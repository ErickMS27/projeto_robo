
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

// Velocidade de 255 cm/μs de ré e 255 cm/μs de frente para cada lado.
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

// Desabilita as pontes: parada por roda livre.
void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  acionado = false;
}

// Enables em HIGH com IN1 = IN2 e IN3 = IN4.
void frearMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
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
