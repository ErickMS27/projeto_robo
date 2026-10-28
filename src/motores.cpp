#include <Arduino.h>
#include "config.h"
#include "motores.h"

static int aplicarAjuste(int velocidade, int ajuste) {
  if (velocidade > 0) return constrain(velocidade + ajuste, 0, 255);
  if (velocidade < 0) return constrain(velocidade - ajuste, -255, 0);
  return 0;
}

static void acionarLado(uint8_t pinoEnable, uint8_t pinoA, uint8_t pinoB,
                        int velocidade, bool invertido) {
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

void motoresIniciar() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  motoresParar();
}

void motoresMover(int velocidadeEsquerda, int velocidadeDireita) {
  velocidadeEsquerda = constrain(velocidadeEsquerda, -255, 255);
  velocidadeDireita = constrain(velocidadeDireita, -255, 255);
  acionarLado(ENA, IN1, IN2, aplicarAjuste(velocidadeEsquerda, AJUSTE_PWM_ESQUERDO),
              INVERTER_LADO_ESQUERDO);
  acionarLado(ENB, IN3, IN4, aplicarAjuste(velocidadeDireita, AJUSTE_PWM_DIREITO),
              INVERTER_LADO_DIREITO);
}

void motoresParar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void motoresFrear() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}
