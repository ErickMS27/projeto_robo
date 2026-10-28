// Configuração do carrinho autônomo ROB4M.
//
// Pinagem conforme docs/pinagem.md (seção 7 do manual). Ao alterar um pino,
// atualizar também a documentação, os demais sketches e as etiquetas dos
// chicotes. Os parâmetros marcados "calibrar" dependem dos ensaios de bancada.

#ifndef CONFIG_H
#define CONFIG_H

#define VERSAO_FIRMWARE "0.1.0"
#define VELOCIDADE_SERIAL 9600

// ---------------- Pinagem ----------------

// Ponte H L298N (PWM em D3 e D11, Timer2)
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

// Servos dos ultrassônicos (a biblioteca Servo usa o Timer1)
#define SERVO_ESQ_PIN 9
#define SERVO_DIR_PIN 10

// Sensores
#define IR_PIN 2   // D2 = interrupção externa INT0
#define TRIG1 A0   // US1 (esquerdo)
#define ECHO1 A1
#define TRIG2 A2   // US2 (direito)
#define ECHO2 A3

// ---------------- Convenções a confirmar na bancada ----------------

// Nível do IR que indica obstáculo. O manual adota LOW; confirmar no T03.
#define IR_NIVEL_OBSTACULO LOW

// Inverte a convenção de comando de um lado inteiro (seção 6 do manual),
// conforme o resultado do T06 registrado pela Montagem. Um motor invertido
// dentro do par deve ser corrigido nos fios, não aqui.
#define INVERTER_LADO_ESQUERDO false
#define INVERTER_LADO_DIREITO false

// ---------------- Velocidades (PWM de 0 a 255) ----------------

#define VELOCIDADE_CRUZEIRO 150  // mesmo valor do programa de teste
#define VELOCIDADE_CAUTELA 110   // obstáculo próximo ou sem leitura válida (calibrar)
#define VELOCIDADE_MANOBRA 140   // ré e giros (calibrar)

// Correção de desvio em linha reta, sem encoders: somada ao PWM do lado.
// Ex.: se o carrinho puxa para a esquerda, aumentar AJUSTE_PWM_ESQUERDO.
#define AJUSTE_PWM_ESQUERDO 0
#define AJUSTE_PWM_DIREITO 0

// ---------------- Distâncias (cm) ----------------

#define DISTANCIA_PARADA_CM 20   // freia e procura outro caminho (calibrar)
#define DISTANCIA_CAUTELA_CM 45  // reduz para VELOCIDADE_CAUTELA (calibrar)
#define DISTANCIA_MIN_VALIDA_CM 2
#define DISTANCIA_MAX_VALIDA_CM 400

// Valor dado a um lado sem eco na varredura: transitável, mas com prioridade
// menor que uma leitura livre confirmada.
#define DISTANCIA_SEM_ECO_CM DISTANCIA_CAUTELA_CM

// ---------------- Ultrassônicos ----------------

#define TIMEOUT_ECO_US 30000UL
// Intervalo entre disparos alternados de US1 e US2 (cada sensor a cada 2x)
#define INTERVALO_DISPARO_MS 35
// Leituras inválidas seguidas a partir das quais a última válida é descartada
#define LIMITE_LEITURAS_INVALIDAS 3

// ---------------- Servos ----------------

#define ANGULO_CENTRO 90
// Ângulos de varredura: manter dentro dos limites aprovados no T04 e conferir
// para que lado cada servo gira (calibrar).
#define ANGULO_OLHAR_ESQUERDA 135  // SV1
#define ANGULO_OLHAR_DIREITA 45    // SV2

// ---------------- Tempos (ms) ----------------

#define TEMPO_ESPERA_INICIAL_MS 3000UL  // motores desligados após ligar ou retomar
#define TEMPO_FRENAGEM_MS 250UL
#define TEMPO_RE_MS 400UL
#define TEMPO_ACOMODAR_SERVOS_MS 400UL
// Sem encoders o giro é feito por tempo: calibrar no piso de operação.
#define TEMPO_GIRO_90_MS 450UL
#define TEMPO_GIRO_180_MS 900UL
#define INTERVALO_TELEMETRIA_MS 500UL

#endif
