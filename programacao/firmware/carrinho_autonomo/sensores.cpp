#include <Arduino.h>
#include "config.h"
#include "sensores.h"

struct Ultrassom {
  uint8_t trig;
  uint8_t echo;
  long distanciaCm;           // última leitura válida
  uint8_t invalidasSeguidas;
};

static Ultrassom ultrassons[2] = {
  {TRIG1, ECHO1, 0, LIMITE_LEITURAS_INVALIDAS},
  {TRIG2, ECHO2, 0, LIMITE_LEITURAS_INVALIDAS},
};

static uint8_t proximoSensor = 0;
static unsigned long ultimoDisparo = 0;

void sensoresIniciar() {
  pinMode(IR_PIN, INPUT);
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(ultrassons[i].trig, OUTPUT);
    pinMode(ultrassons[i].echo, INPUT);
    digitalWrite(ultrassons[i].trig, LOW);
  }
}

long lerDistancia(uint8_t trigPin, uint8_t echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duracao = pulseIn(echoPin, HIGH, TIMEOUT_ECO_US);
  long distancia = (long)(duracao * 0.034 / 2);
  if (distancia < DISTANCIA_MIN_VALIDA_CM || distancia > DISTANCIA_MAX_VALIDA_CM) return 0;
  return distancia;
}

long lerDistanciaMediana(uint8_t trigPin, uint8_t echoPin) {
  long a = lerDistancia(trigPin, echoPin);
  delay(INTERVALO_DISPARO_MS);
  long b = lerDistancia(trigPin, echoPin);
  delay(INTERVALO_DISPARO_MS);
  long c = lerDistancia(trigPin, echoPin);

  // ordena os três valores; o do meio é a mediana
  long t;
  if (a > b) { t = a; a = b; b = t; }
  if (b > c) { t = b; b = c; c = t; }
  if (a > b) { t = a; a = b; b = t; }
  return b;
}

void ultrassomAtualizar() {
  if (millis() - ultimoDisparo < INTERVALO_DISPARO_MS) return;
  ultimoDisparo = millis();

  Ultrassom &sensor = ultrassons[proximoSensor];
  long distancia = lerDistancia(sensor.trig, sensor.echo);
  if (distancia > 0) {
    sensor.distanciaCm = distancia;
    sensor.invalidasSeguidas = 0;
  } else if (sensor.invalidasSeguidas < LIMITE_LEITURAS_INVALIDAS) {
    sensor.invalidasSeguidas++;
  }
  proximoSensor = 1 - proximoSensor;
}

void ultrassomReiniciar() {
  for (uint8_t i = 0; i < 2; i++) {
    ultrassons[i].distanciaCm = 0;
    ultrassons[i].invalidasSeguidas = LIMITE_LEITURAS_INVALIDAS;
  }
}

static long distanciaRecente(const Ultrassom &sensor) {
  return sensor.invalidasSeguidas < LIMITE_LEITURAS_INVALIDAS ? sensor.distanciaCm : 0;
}

long distanciaEsquerda() {
  return distanciaRecente(ultrassons[0]);
}

long distanciaDireita() {
  return distanciaRecente(ultrassons[1]);
}

bool irDetectaObstaculo() {
  return digitalRead(IR_PIN) == IR_NIVEL_OBSTACULO;
}
