// Leitura dos ultrassônicos US1 (esquerdo) e US2 (direito) e do IR frontal.
//
// Distância 0 significa "sem leitura válida" (sem eco, timeout ou fora da
// faixa do sensor), nunca uma distância física (manual, seção 10).

#ifndef SENSORES_H
#define SENSORES_H

#include <Arduino.h>

void sensoresIniciar();

// Leitura única e bloqueante (até TIMEOUT_ECO_US). Distância em cm ou 0.
long lerDistancia(uint8_t trigPin, uint8_t echoPin);

// Mediana de três leituras, para decisões com o carrinho parado.
long lerDistanciaMediana(uint8_t trigPin, uint8_t echoPin);

// Dispara um ultrassônico por chamada, alternando US1 e US2, sempre que
// INTERVALO_DISPARO_MS tiver passado. Chamar a cada volta do loop.
void ultrassomAtualizar();

// Descarta as leituras anteriores (usar depois de manobras).
void ultrassomReiniciar();

// Última distância válida de cada lado em cm; 0 = sem leitura válida recente.
long distanciaEsquerda();
long distanciaDireita();

bool irDetectaObstaculo();

#endif
