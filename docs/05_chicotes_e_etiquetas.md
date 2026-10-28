# Chicotes e etiquetas

Etiquetar nas **duas extremidades**. A cor do cabo não determina o sentido de avanço: anotar a cor
apenas como apoio e registrar qualquer inversão feita depois do ensaio de sentido.

## Motores

| Etiqueta | Motor | Terminal | Borne do L298N | Cor do fio | Invertido após ensaio? |
|---|---|---|---|---|---|
| ME1-a | Esquerdo dianteiro | Primeiro | OUT1 | | |
| ME1-b | Esquerdo dianteiro | Outro | OUT2 | | |
| ME2-a | Esquerdo traseiro | Primeiro | OUT1 | | |
| ME2-b | Esquerdo traseiro | Outro | OUT2 | | |
| MD1-a | Direito dianteiro | Primeiro | OUT3 | | |
| MD1-b | Direito dianteiro | Outro | OUT4 | | |
| MD2-a | Direito traseiro | Primeiro | OUT3 | | |
| MD2-b | Direito traseiro | Outro | OUT4 | | |

## Servos e sensores

| Etiqueta | Fio | Origem | Destino | Cor do fio |
|---|---|---|---|---|
| SV1 | Sinal | Servo esquerdo | D9 | |
| SV1 | VCC | Servo esquerdo | LM2596 OUT+ | |
| SV1 | GND | Servo esquerdo | GND comum | |
| SV2 | Sinal | Servo direito | D10 | |
| SV2 | VCC | Servo direito | LM2596 OUT+ | |
| SV2 | GND | Servo direito | GND comum | |
| US1 | TRIG | Ultrassônico esquerdo | A0 | |
| US1 | ECHO | Ultrassônico esquerdo | A1 | |
| US1 | VCC / GND | Ultrassônico esquerdo | 5V do Uno / GND comum | |
| US2 | TRIG | Ultrassônico direito | A2 | |
| US2 | ECHO | Ultrassônico direito | A3 | |
| US2 | VCC / GND | Ultrassônico direito | 5V do Uno / GND comum | |
| IR | OUT | Sensor frontal | D2 | |
| IR | VCC / GND | Sensor frontal | 5V do Uno / GND comum | |

## Controle da ponte H

| Sinal | Uno | L298N | Cor do fio |
|---|---|---|---|
| PWM esquerdo | D3 | ENA | |
| Direção esquerda | D4 | IN1 | |
| Direção esquerda | D5 | IN2 | |
| Direção direita | D6 | IN3 | |
| Direção direita | D7 | IN4 | |
| PWM direito | D11 | ENB | |
| Lógica 5 V | 5V | Borne 5V | |
| Referência | GND | GND | |

## Registro de inversões

| Data | Motor ou lado | O que foi invertido | Motivo | Responsável |
|---|---|---|---|---|
| | | | | |

Se a correção for feita no software (`INVERTER_ESQUERDO` / `INVERTER_DIREITO` no
[bancada_motores](firmware/bancada_motores/bancada_motores.ino) e `INVERTER_LADO_*` no
[config.h](../programacao/firmware/carrinho_autonomo/config.h)), registrar aqui também e avisar a
Programação.
