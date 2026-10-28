
#ifndef SENSORES_H
#define SENSORES_H

#include <Arduino.h>

void sensoresIniciar();

long lerDistancia(uint8_t trigPin, uint8_t echoPin);
long lerDistanciaMediana(uint8_t trigPin, uint8_t echoPin);

void ultrassomAtualizar();
void ultrassomReiniciar();

long distanciaEsquerda();
long distanciaDireita();

bool irDetectaObstaculo();

#endif
