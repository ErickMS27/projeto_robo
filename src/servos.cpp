#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "servos.h"

static Servo servoEsquerdo;
static Servo servoDireito;

void servosIniciar() {
  servoEsquerdo.attach(SERVO_ESQ_PIN);
  servoDireito.attach(SERVO_DIR_PIN);
  servosCentralizar();
}

void servosCentralizar() {
  servoEsquerdo.write(ANGULO_CENTRO);
  servoDireito.write(ANGULO_CENTRO);
}

void servosOlharLados() {
  servoEsquerdo.write(ANGULO_OLHAR_ESQUERDA);
  servoDireito.write(ANGULO_OLHAR_DIREITA);
}
