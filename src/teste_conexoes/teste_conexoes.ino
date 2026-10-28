
#include <Servo.h>

// Pinos da ponte H
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

Servo servoEsquerdo;
Servo servoDireito;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  servoEsquerdo.attach(9);
  servoDireito.attach(10);
  servoEsquerdo.write(90);
  servoDireito.write(90);
  delay(2000);
}

void loop() {
  int estadoIR = digitalRead(IR_PIN);
  Serial.print("IR: ");
  Serial.print(estadoIR == 0 ? "Obstaculo! | " : "Livre | ");

  Serial.print("Dist 1: ");
  Serial.print(lerDistancia(TRIG1, ECHO1));
  Serial.print(" cm | ");
  Serial.print("Dist 2: ");
  Serial.print(lerDistancia(TRIG2, ECHO2));
  Serial.println(" cm");

  moverFrente(150);
  delay(2000);
  pararMotores();
  delay(2000);
}

long lerDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH, 30000);
  return duracao * 0.034 / 2;
}

void moverFrente(int velocidade) {
  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
