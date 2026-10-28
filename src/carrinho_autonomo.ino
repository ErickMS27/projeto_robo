
#include "config.h"
#include "motores.h"
#include "sensores.h"
#include "servos.h"

enum Estado {
  AGUARDANDO_PARTIDA,
  AVANCANDO,
  FREANDO,
  RECUANDO,
  VARRENDO,
  GIRANDO,
  PAUSADO
};

Estado estado = AGUARDANDO_PARTIDA;
unsigned long inicioEstado = 0;

bool freouPorIR = false;      // decide a manobra depois da frenagem
int sentidoGiro = -1;         // -1 = Left, +1 = Right
unsigned long duracaoGiro = 0;
int velocidadeAvanco = 0;
int comandoEsquerdo = 0;
int comandoDireito = 0;
unsigned long ultimaTelemetria = 0;

// Compartilhadas com a interrupção do IR
volatile bool avancoBloqueado = false;
volatile bool movendoFrente = false;

void entrarEstado(Estado novo);
const __FlashStringHelper *nomeEstado(Estado e);

void setup() {
  Serial.begin(VELOCIDADE_SERIAL);
  motoresIniciar();
  sensoresIniciar();
  servosIniciar();

  avancoBloqueado = irDetectaObstaculo();
  attachInterrupt(digitalPinToInterrupt(IR_PIN), aoMudarIR, CHANGE);

  Serial.print(F("ROB4M - carrinho autonomo v"));
  Serial.println(F(VERSAO_FIRMWARE));
  Serial.println(F("Comandos: p = pausar | c = continuar | ? = estado"));
  entrarEstado(AGUARDANDO_PARTIDA);
}

void loop() {
  lerComandoSerial();

  switch (estado) {
    case AGUARDANDO_PARTIDA:
      ultrassomAtualizar();
      if (tempoNoEstado() >= TEMPO_ESPERA_INICIAL_MS) entrarEstado(AVANCANDO);
      break;
    case AVANCANDO:
      atualizarAvanco();
      break;
    case FREANDO:
      if (tempoNoEstado() >= TEMPO_FRENAGEM_MS) entrarEstado(freouPorIR ? RECUANDO : VARRENDO);
      break;
    case RECUANDO:
      if (tempoNoEstado() >= TEMPO_RE_MS) entrarEstado(VARRENDO);
      break;
    case VARRENDO:
      if (tempoNoEstado() >= TEMPO_ACOMODAR_SERVOS_MS) decidirGiro();
      break;
    case GIRANDO:
      if (tempoNoEstado() >= duracaoGiro) entrarEstado(AVANCANDO);
      break;
    case PAUSADO:
      ultrassomAtualizar();
      break;
  }

  imprimirTelemetria();
}

// ---------------- SINALIZAÇÃO DE EMERGÊNCIA IR ----------------

void aoMudarIR() {
  if (digitalRead(IR_PIN) != IR_NIVEL_OBSTACULO) return;
  avancoBloqueado = true;
  if (movendoFrente) {
    motoresFrear();
    movendoFrente = false;
  }
}

bool comandarMotores(int velocidadeEsquerda, int velocidadeDireita) {
  bool frente = velocidadeEsquerda + velocidadeDireita > 0;
  bool aceito = true;

  noInterrupts();
  if (frente && avancoBloqueado) {
    aceito = false;
  } else {
    motoresMover(velocidadeEsquerda, velocidadeDireita);
    movendoFrente = frente;
  }
  interrupts();

  if (aceito) {
    comandoEsquerdo = velocidadeEsquerda;
    comandoDireito = velocidadeDireita;
  }
  return aceito;
}

void frear() {
  noInterrupts();
  motoresFrear();
  movendoFrente = false;
  interrupts();
  comandoEsquerdo = 0;
  comandoDireito = 0;
}

void liberarAvanco() {
  noInterrupts();
  if (!irDetectaObstaculo()) avancoBloqueado = false;
  interrupts();
}

// ---------------- STATUS ----------------

void entrarEstado(Estado novo) {
  estado = novo;
  inicioEstado = millis();

  switch (novo) {
    case AGUARDANDO_PARTIDA:
    case PAUSADO:
      comandarMotores(0, 0);
      servosCentralizar();
      velocidadeAvanco = 0;
      break;
    case AVANCANDO:
      liberarAvanco();
      ultrassomReiniciar();
      velocidadeAvanco = 0;
      break;
    case FREANDO:
      frear();
      velocidadeAvanco = 0;
      break;
    case RECUANDO:
      comandarMotores(-VELOCIDADE_MANOBRA, -VELOCIDADE_MANOBRA);
      break;
    case VARRENDO:
      comandarMotores(0, 0);
      servosOlharLados();
      break;
    case GIRANDO:
      servosCentralizar();
      comandarMotores(sentidoGiro * VELOCIDADE_MANOBRA, -sentidoGiro * VELOCIDADE_MANOBRA);
      break;
  }
}

unsigned long tempoNoEstado() {
  return millis() - inicioEstado;
}

void atualizarAvanco() {
  if (avancoBloqueado || irDetectaObstaculo()) {
    freouPorIR = true;
    entrarEstado(FREANDO);
    return;
  }

  ultrassomAtualizar();
  if (velocidadeAvanco == 0 && tempoNoEstado() < 2 * INTERVALO_DISPARO_MS) return;

  long esquerda = distanciaEsquerda();
  long direita = distanciaDireita();

  if (obstaculoAte(esquerda, DISTANCIA_PARADA_CM) || obstaculoAte(direita, DISTANCIA_PARADA_CM)) {
    freouPorIR = false;
    entrarEstado(FREANDO);
    return;
  }

  bool semLeitura = esquerda == 0 || direita == 0;
  bool proximo = obstaculoAte(esquerda, DISTANCIA_CAUTELA_CM) ||
                 obstaculoAte(direita, DISTANCIA_CAUTELA_CM);
  int velocidade = (semLeitura || proximo) ? VELOCIDADE_CAUTELA : VELOCIDADE_CRUZEIRO;

  if (velocidade == velocidadeAvanco) return;
  if (!comandarMotores(velocidade, velocidade)) {
    freouPorIR = true;
    entrarEstado(FREANDO);
    return;
  }
  velocidadeAvanco = velocidade;
}

bool obstaculoAte(long distancia, long limite) {
  return distancia > 0 && distancia <= limite;
}

void decidirGiro() {
  long esquerda = lerDistanciaMediana(TRIG1, ECHO1);
  delay(INTERVALO_DISPARO_MS);
  long direita = lerDistanciaMediana(TRIG2, ECHO2);

  imprimirDistancia(F("Varredura | esq: "), esquerda);
  imprimirDistancia(F(" | dir: "), direita);
  Serial.println();

  long livreEsquerda = esquerda > 0 ? esquerda : DISTANCIA_SEM_ECO_CM;
  long livreDireita = direita > 0 ? direita : DISTANCIA_SEM_ECO_CM;

  if (livreEsquerda <= DISTANCIA_PARADA_CM && livreDireita <= DISTANCIA_PARADA_CM) {
    sentidoGiro = -1;
    duracaoGiro = TEMPO_GIRO_180_MS;
  } else if (livreEsquerda >= livreDireita) {
    sentidoGiro = -1;
    duracaoGiro = TEMPO_GIRO_90_MS;
  } else {
    sentidoGiro = 1;
    duracaoGiro = TEMPO_GIRO_90_MS;
  }
  entrarEstado(GIRANDO);
}

// ---------------- SERIAL ----------------

void lerComandoSerial() {
  if (!Serial.available()) return;

  char comando = Serial.read();
  if (comando == 'p') {
    entrarEstado(PAUSADO);
    Serial.println(F("Pausado"));
  } else if (comando == 'c' && estado == PAUSADO) {
    entrarEstado(AGUARDANDO_PARTIDA);
    Serial.println(F("Retomando apos a espera inicial"));
  } else if (comando == '?') {
    imprimirEstado();
  }
}

void imprimirTelemetria() {
  if (millis() - ultimaTelemetria < INTERVALO_TELEMETRIA_MS) return;
  ultimaTelemetria = millis();
  imprimirEstado();
}

void imprimirEstado() {
  Serial.print(nomeEstado(estado));
  Serial.print(irDetectaObstaculo() ? F(" | IR: Obstaculo") : F(" | IR: Livre"));
  imprimirDistancia(F(" | US1: "), distanciaEsquerda());
  imprimirDistancia(F(" | US2: "), distanciaDireita());
  Serial.print(F(" | E: "));
  Serial.print(comandoEsquerdo);
  Serial.print(F(" D: "));
  Serial.println(comandoDireito);
}

void imprimirDistancia(const __FlashStringHelper *rotulo, long distancia) {
  Serial.print(rotulo);
  if (distancia == 0) {
    Serial.print(F("sem leitura"));
    return;
  }
  Serial.print(distancia);
  Serial.print(F(" cm"));
}

const __FlashStringHelper *nomeEstado(Estado e) {
  switch (e) {
    case AGUARDANDO_PARTIDA: return F("AGUARDANDO");
    case AVANCANDO: return F("AVANCANDO");
    case FREANDO: return F("FREANDO");
    case RECUANDO: return F("RECUANDO");
    case VARRENDO: return F("VARRENDO");
    case GIRANDO: return F("GIRANDO");
    case PAUSADO: return F("PAUSADO");
  }
  return F("?");
}
