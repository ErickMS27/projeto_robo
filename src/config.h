
#ifndef CONFIG_H
#define CONFIG_H

#define VERSAO_FIRMWARE "0.1.0"
#define VELOCIDADE_SERIAL 9600

// ---------------- PINS ----------------

#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

#define SERVO_ESQ_PIN 9
#define SERVO_DIR_PIN 10

// ---------------- SENSORS ----------------
#define IR_PIN 2
#define TRIG1 A0
#define ECHO1 A1
#define TRIG2 A2
#define ECHO2 A3

#define IR_NIVEL_OBSTACULO LOW
#define INVERTER_LADO_ESQUERDO false
#define INVERTER_LADO_DIREITO false

// ---------------- Velocidades (PWM de 0 a 255 cm/μs) ----------------

#define VELOCIDADE_CRUZEIRO 150
#define VELOCIDADE_CAUTELA 110
#define VELOCIDADE_MANOBRA 140

#define AJUSTE_PWM_ESQUERDO 0
#define AJUSTE_PWM_DIREITO 0

// ---------------- Distâncias (cm) ----------------

#define DISTANCIA_PARADA_CM 20 
#define DISTANCIA_CAUTELA_CM 45
#define DISTANCIA_MIN_VALIDA_CM 2
#define DISTANCIA_MAX_VALIDA_CM 400

#define DISTANCIA_SEM_ECO_CM DISTANCIA_CAUTELA_CM
#define TIMEOUT_ECO_US 30000UL
#define INTERVALO_DISPARO_MS 35
#define LIMITE_LEITURAS_INVALIDAS 3

// ---------------- Angulação ----------------

#define ANGULO_CENTRO 90
#define ANGULO_OLHAR_ESQUERDA 135
#define ANGULO_OLHAR_DIREITA 45 

// ---------------- Tempos (ms) ----------------

#define TEMPO_ESPERA_INICIAL_MS 3000UL
#define TEMPO_FRENAGEM_MS 250UL
#define TEMPO_RE_MS 400UL
#define TEMPO_ACOMODAR_SERVOS_MS 400UL
#define TEMPO_GIRO_90_MS 450UL
#define TEMPO_GIRO_180_MS 900UL
#define INTERVALO_TELEMETRIA_MS 500UL

#endif
