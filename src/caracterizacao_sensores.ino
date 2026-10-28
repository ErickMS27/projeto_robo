
#include <Servo.h>

// Pinos da ponte H (mantidos desligados)
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

// Pinos dos servos e sensores
#define SERVO_ESQ_PIN 9
#define SERVO_DIR_PIN 10
#define IR_PIN 2
#define TRIG1 A0
#define ECHO1 A1
#define TRIG2 A2
#define ECHO2 A3

#define TIMEOUT_ECO_US 30000UL
#define INTERVALO_ENTRE_DISPAROS_MS 60
#define NUM_AMOSTRAS 50
#define DURACAO_ENSAIO_IR_MS 10000UL

Servo servoEsquerdo;
Servo servoDireito;

struct Estatistica {
  unsigned int validas;
  float soma;
  float somaQuadrados;
  float minimo;
  float maximo;
};

void setup() {
  Serial.begin(9600);
  desligarPonteH();

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);

  servoEsquerdo.attach(SERVO_ESQ_PIN);
  servoDireito.attach(SERVO_DIR_PIN);
  servoEsquerdo.write(90);
  servoDireito.write(90);

  Serial.println(F("ROB4M - caracterizacao dos sensores"));
  mostrarAjuda();
}

void loop() {
  if (!Serial.available()) return;

  switch (Serial.read()) {
    case 'u': ensaiarUltrassom(false); break;
    case 'r': ensaiarUltrassom(true); break;
    case 'i': ensaiarIR(); break;
    case '?': mostrarAjuda(); break;
  }
}

// ---------------- SENSOR ULTRASSÔNICO ----------------

void ensaiarUltrassom(bool csv) {
  Estatistica us1;
  Estatistica us2;
  zerar(us1);
  zerar(us2);

  if (csv) {
    Serial.println(F("amostra;us1_eco_us;us2_eco_us"));
  } else {
    Serial.print(F("Coletando "));
    Serial.print(NUM_AMOSTRAS);
    Serial.println(F(" amostras de cada sensor..."));
  }

  for (int i = 1; i <= NUM_AMOSTRAS; i++) {
    unsigned long eco1 = medirEco(TRIG1, ECHO1);
    delay(INTERVALO_ENTRE_DISPAROS_MS);
    unsigned long eco2 = medirEco(TRIG2, ECHO2);
    delay(INTERVALO_ENTRE_DISPAROS_MS);

    if (eco1 > 0) acumular(us1, eco1 * 0.034 / 2);
    if (eco2 > 0) acumular(us2, eco2 * 0.034 / 2);

    if (csv) {
      Serial.print(i);
      Serial.print(';');
      Serial.print(eco1);
      Serial.print(';');
      Serial.println(eco2);
    }
  }

  if (!csv) {
    imprimirResumo(F("US1"), us1);
    imprimirResumo(F("US2"), us2);
  }
}

// Duração do pulso ECHO em microssegundos.
unsigned long medirEco(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, TIMEOUT_ECO_US);
}

void zerar(Estatistica &e) {
  e.validas = 0;
  e.soma = 0;
  e.somaQuadrados = 0;
  e.minimo = 0;
  e.maximo = 0;
}

void acumular(Estatistica &e, float cm) {
  if (e.validas == 0 || cm < e.minimo) e.minimo = cm;
  if (e.validas == 0 || cm > e.maximo) e.maximo = cm;
  e.validas++;
  e.soma += cm;
  e.somaQuadrados += cm * cm;
}

void imprimirResumo(const __FlashStringHelper *nome, const Estatistica &e) {
  Serial.print(nome);
  Serial.print(F(": validas "));
  Serial.print(e.validas);
  Serial.print('/');
  Serial.print(NUM_AMOSTRAS);
  if (e.validas == 0) {
    Serial.println(F(" | sem leitura valida"));
    return;
  }
  float media = e.soma / e.validas;
  float variancia = e.somaQuadrados / e.validas - media * media;
  if (variancia < 0) variancia = 0;

  Serial.print(F(" | media "));
  Serial.print(media, 1);
  Serial.print(F(" cm | min "));
  Serial.print(e.minimo, 1);
  Serial.print(F(" | max "));
  Serial.print(e.maximo, 1);
  Serial.print(F(" | desvio "));
  Serial.print(sqrt(variancia), 2);
  Serial.println(F(" cm"));
}

// ---------------- SENSOR INFRAVERMELHO ----------------

void ensaiarIR() {
  Serial.println(F("IR: observando por 10 s. Comece sem alvo, depois aproxime e afaste."));

  unsigned long inicio = millis();
  unsigned long ultimoInstante = inicio;
  unsigned long tempoEmLow = 0;
  unsigned long transicoes = 0;
  int nivelAnterior = digitalRead(IR_PIN);

  Serial.print(F("Nivel em repouso: "));
  Serial.println(nivelAnterior == HIGH ? F("HIGH") : F("LOW"));

  while (millis() - inicio < DURACAO_ENSAIO_IR_MS) {
    unsigned long agora = millis();
    int nivel = digitalRead(IR_PIN);
    if (nivelAnterior == LOW) tempoEmLow += agora - ultimoInstante;
    ultimoInstante = agora;

    if (nivel != nivelAnterior) {
      transicoes++;
      Serial.print(agora - inicio);
      Serial.print(F(" ms -> "));
      Serial.println(nivel == HIGH ? F("HIGH") : F("LOW"));
      nivelAnterior = nivel;
    }
  }

  Serial.print(F("Transicoes: "));
  Serial.print(transicoes);
  Serial.print(F(" | tempo em LOW: "));
  Serial.print(tempoEmLow * 100 / DURACAO_ENSAIO_IR_MS);
  Serial.println(F("%"));
  Serial.println(F("Se o nivel vai a LOW com o alvo presente, manter IR_NIVEL_OBSTACULO LOW."));
}

void mostrarAjuda() {
  Serial.println(F("u = estatistica US1/US2 | r = CSV US1/US2 | i = ensaio do IR | ? = ajuda"));
}

void desligarPonteH() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}
