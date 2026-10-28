
// Pinos da ponte H (mantidos desligados)
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

// Pinos dos sensores
#define IR_PIN 2
#define TRIG1 A0
#define ECHO1 A1
#define TRIG2 A2
#define ECHO2 A3

// Leitor do nível do IR que indica obstáculo.
#define IR_NIVEL_OBSTACULO LOW

#define TIMEOUT_ECO_US 30000UL
#define INTERVALO_ENTRE_SENSORES_MS 60
#define INTERVALO_CICLO_MS 500

unsigned long ciclos = 0;
unsigned long semEco1 = 0;
unsigned long semEco2 = 0;

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

  Serial.println(F("ROB4M - teste de sensores (T03)"));
  Serial.println(F("Use um alvo a distancia conhecida diante de cada sensor."));
}

void loop() {
  unsigned long eco1 = medirEco(TRIG1, ECHO1);
  delay(INTERVALO_ENTRE_SENSORES_MS);
  unsigned long eco2 = medirEco(TRIG2, ECHO2);
  int estadoIR = digitalRead(IR_PIN);

  ciclos++;
  if (eco1 == 0) semEco1++;
  if (eco2 == 0) semEco2++;

  Serial.print(F("IR: "));
  Serial.print(estadoIR == HIGH ? F("HIGH") : F("LOW"));
  Serial.print(estadoIR == IR_NIVEL_OBSTACULO ? F(" (Obstaculo)") : F(" (Livre)"));
  imprimirDistancia(F(" | US1: "), eco1);
  imprimirDistancia(F(" | US2: "), eco2);
  Serial.print(F(" | sem eco US1 "));
  Serial.print(semEco1);
  Serial.print('/');
  Serial.print(ciclos);
  Serial.print(F(" US2 "));
  Serial.print(semEco2);
  Serial.print('/');
  Serial.println(ciclos);

  delay(INTERVALO_CICLO_MS);
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

void imprimirDistancia(const __FlashStringHelper *rotulo, unsigned long eco) {
  Serial.print(rotulo);
  if (eco == 0) {
    Serial.print(F("sem eco"));
    return;
  }
  Serial.print(eco * 0.034 / 2, 1);
  Serial.print(F(" cm ("));
  Serial.print(eco);
  Serial.print(F(" us)"));
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
