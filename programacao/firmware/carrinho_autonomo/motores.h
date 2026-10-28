// Acionamento dos dois lados pela ponte H L298N.
// Canal A (ENA, IN1, IN2): ME1 e ME2. Canal B (ENB, IN3, IN4): MD1 e MD2.

#ifndef MOTORES_H
#define MOTORES_H

void motoresIniciar();

// Velocidade de cada lado de -255 (ré) a 255 (frente); 0 deixa o lado livre.
// Aplica INVERTER_LADO_* e AJUSTE_PWM_* do config.h.
void motoresMover(int velocidadeEsquerda, int velocidadeDireita);

// Desabilita as pontes (ENA e ENB em zero): parada por roda livre,
// igual a pararMotores do programa de teste.
void motoresParar();

// Frenagem ativa: enables em HIGH e entradas no mesmo nível
// ("fast motor stop" na tabela de controle do L298).
// Usa apenas digitalWrite e pode ser chamada dentro de interrupção.
void motoresFrear();

#endif
