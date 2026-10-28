/*
 * ROB4M - Programa de bancada dos motores (ensaios T05, T06 e T07)
 *
 * Aciona cada lado separadamente ou os dois juntos por comandos no monitor
 * serial. Todo acionamento é desligado automaticamente após TEMPO_MAXIMO_MS.
 *
 * Manter o chassi suspenso. Os dois motores de cada lado estão em paralelo
 * no mesmo canal da ponte H: para ensaiar um motor de cada vez (T05),
 * desconectar o outro motor do par com as fontes retiradas (seção 11).
 *
 * Se um lado inteiro girar ao contrário, é possível inverter os fios dos dois
 * motores do lado ou usar INVERTER_ESQUERDO / INVERTER_DIREITO. Um único motor
 * invertido dentro do par só se corrige nos fios. Registrar a escolha no
 * Apêndice B e repassar à Programação (config.h do carrinho_autonomo).
 *
 * Comandos (monitor serial 9600 baud):
 *   e / E   lado esquerdo (ME1 + ME2) frente / ré
 *   d / D   lado direito (MD1 + MD2) frente / ré
 *   f / t   dois lados frente / ré
 *   < / >   giro no lugar para a esquerda / direita
 *   + / -   aumenta / reduz o PWM em PASSO_PWM (vale para o próximo comando)
 *   b       frenagem ativa (enables em HIGH e entradas no mesmo nível)
 *   r       repete NUM_PARTIDAS partidas dos dois lados (T07)
 *   x       desaciona (roda livre); espaço também desaciona
 *   ?       mostra os comandos
 */

// Pinos da ponte H
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

#define INVERTER_ESQUERDO false
#define INVERTER_DIREITO false

#define PWM_INICIAL 150
#define PASSO_PWM 10
#define TEMPO_MAXIMO_MS 3000UL
// Pausa antes de mudar o comando com o motor girando
#define PAUSA_TROCA_MS 300

// Ensaio de partidas repetidas (T07)
#define NUM_PARTIDAS 10
#define TEMPO_PARTIDA_LIGADO_MS 1000UL
#define TEMPO_PARTIDA_DESLIGADO_MS 1000UL

int pwm = PWM_INICIAL;
bool acionado = false;
unsigned long inicioAcionamento = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pararMotores();

  Serial.println(F("ROB4M - bancada dos motores (T05 a T07)"));
  Serial.println(F("Chassi suspenso! Cada acionamento desliga sozinho apos 3 s."));
  mostrarAjuda();
}

void loop() {
  if (acionado && millis() - inicioAcionamento >= TEMPO_MAXIMO_MS) {
    pararMotores();
    Serial.println(F("Tempo maximo atingido: motores desacionados"));
  }

  if (!Serial.available()) return;

  char comando = Serial.read();
  switch (comando) {
    case 'e': acionar(pwm, 0, F("Esquerdo frente")); break;
    case 'E': acionar(-pwm, 0, F("Esquerdo re")); break;
    case 'd': acionar(0, pwm, F("Direito frente")); break;
    case 'D': acionar(0, -pwm, F("Direito re")); break;
    case 'f': acionar(pwm, pwm, F("Dois lados frente")); break;
    case 't': acionar(-pwm, -pwm, F("Dois lados re")); break;
    case '<': acionar(-pwm, pwm, F("Giro a esquerda")); break;
    case '>': acionar(pwm, -pwm, F("Giro a direita")); break;
    case '+': alterarPwm(PASSO_PWM); break;
    case '-': alterarPwm(-PASSO_PWM); break;
    case 'b':
      frearMotores();
      Serial.println(F("Frenagem ativa"));
      break;
    case 'r': repetirPartidas(); break;
    case 'x':
    case ' ':
      pararMotores();
      Serial.println(F("Desacionado (roda livre)"));
      break;
    case '?': mostrarAjuda(); break;
  }
}

// velocidade de -255 (ré) a 255 (frente) para cada lado; 0 deixa o lado livre.
void acionar(int velEsquerda, int velDireita, const __FlashStringHelper *descricao) {
  if (acionado) {
    pararMotores();
    delay(PAUSA_TROCA_MS);
  }
  acionarLado(ENA, IN1, IN2, velEsquerda, INVERTER_ESQUERDO);
  acionarLado(ENB, IN3, IN4, velDireita, INVERTER_DIREITO);
  acionado = true;
  inicioAcionamento = millis();

  Serial.print(descricao);
  Serial.print(F(" | PWM "));
  Serial.println(pwm);
}

void acionarLado(int pinoEnable, int pinoA, int pinoB, int velocidade, bool invertido) {
  if (invertido) velocidade = -velocidade;
  if (velocidade > 0) {
    digitalWrite(pinoA, HIGH);
    digitalWrite(pinoB, LOW);
  } else if (velocidade < 0) {
    digitalWrite(pinoA, LOW);
    digitalWrite(pinoB, HIGH);
  } else {
    digitalWrite(pinoA, LOW);
    digitalWrite(pinoB, LOW);
  }
  analogWrite(pinoEnable, abs(velocidade));
}

// Desabilita as pontes: parada por roda livre (igual ao programa de teste).
void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  acionado = false;
}

// Enables em HIGH com IN1 = IN2 e IN3 = IN4: "fast motor stop" do L298.
void frearMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  // conta como acionamento para ser liberada pelo tempo máximo
  acionado = true;
  inicioAcionamento = millis();
}

void alterarPwm(int delta) {
  pwm = constrain(pwm + delta, 0, 255);
  Serial.print(F("PWM: "));
  Serial.print(pwm);
  Serial.print(F(" ("));
  Serial.print(pwm * 100L / 255);
  Serial.println(F("% da escala, vale para o proximo comando)"));
}

void repetirPartidas() {
  Serial.print(F("T07: "));
  Serial.print(NUM_PARTIDAS);
  Serial.println(F(" partidas dos dois lados. Observe VIN, 5 V dos servos e o BMS. 'x' cancela."));

  if (acionado) {
    pararMotores();
    delay(PAUSA_TROCA_MS);
  }
  for (int i = 1; i <= NUM_PARTIDAS; i++) {
    Serial.print(F("Partida "));
    Serial.println(i);
    acionarLado(ENA, IN1, IN2, pwm, INVERTER_ESQUERDO);
    acionarLado(ENB, IN3, IN4, pwm, INVERTER_DIREITO);
    bool continuar = aguardarOuCancelar(TEMPO_PARTIDA_LIGADO_MS);
    pararMotores();
    if (!continuar || !aguardarOuCancelar(TEMPO_PARTIDA_DESLIGADO_MS)) {
      Serial.println(F("Ensaio de partidas cancelado"));
      return;
    }
  }
  Serial.println(F("Ensaio de partidas concluido"));
}

// Aguarda o tempo pedido; retorna false se 'x' ou espaço chegar pela serial.
bool aguardarOuCancelar(unsigned long tempoMs) {
  unsigned long inicio = millis();
  while (millis() - inicio < tempoMs) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 'x' || c == ' ') return false;
    }
  }
  return true;
}

void mostrarAjuda() {
  Serial.println(F("e/E esq frente/re | d/D dir frente/re | f/t ambos frente/re"));
  Serial.println(F("</> giro esq/dir | +/- PWM | b frear | r partidas T07 | x parar | ? ajuda"));
  Serial.print(F("PWM atual: "));
  Serial.println(pwm);
}
