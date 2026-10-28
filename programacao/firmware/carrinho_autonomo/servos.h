// Posicionamento de SV1 e SV2, que orientam os ultrassônicos US1 e US2.

#ifndef SERVOS_H
#define SERVOS_H

void servosIniciar();

// US1 e US2 na orientação frontal de referência (ANGULO_CENTRO).
void servosCentralizar();

// SV1 para a esquerda e SV2 para a direita, para a varredura.
void servosOlharLados();

#endif
