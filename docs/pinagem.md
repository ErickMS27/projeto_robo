# Pinagem oficial do carrinho

Fonte: seção 7 do manual ROB4M MT 001 Rev. 1.0. Esta é a referência única do projeto: se um pino
mudar, atualizar **ao mesmo tempo** esta tabela, todos os sketches (`#define` no início de cada
arquivo e o [config.h](../programacao/firmware/carrinho_autonomo/config.h)) e as etiquetas dos
chicotes.

## Arduino Uno

| Pino do Uno | Destino | Função | Nome no código |
|---|---|---|---|
| D3 | ENA do L298N | PWM do lado esquerdo | `ENA` |
| D4 | IN1 do L298N | Direção do lado esquerdo | `IN1` |
| D5 | IN2 do L298N | Direção do lado esquerdo | `IN2` |
| D6 | IN3 do L298N | Direção do lado direito | `IN3` |
| D7 | IN4 do L298N | Direção do lado direito | `IN4` |
| D11 | ENB do L298N | PWM do lado direito | `ENB` |
| D9 | Sinal de SV1 | Posição do servo esquerdo | `SERVO_ESQ_PIN` |
| D10 | Sinal de SV2 | Posição do servo direito | `SERVO_DIR_PIN` |
| D2 | OUT do sensor IR | Leitura digital frontal | `IR_PIN` |
| A0 | TRIG de US1 | Disparo do ultrassônico esquerdo | `TRIG1` |
| A1 | ECHO de US1 | Leitura do eco esquerdo | `ECHO1` |
| A2 | TRIG de US2 | Disparo do ultrassônico direito | `TRIG2` |
| A3 | ECHO de US2 | Leitura do eco direito | `ECHO2` |
| 5V | VCC de US1, US2 e IR; lógica do L298N | Alimentação de baixa corrente | — |
| GND | Ponto comum ligado ao P- protegido | Referência elétrica compartilhada | — |

## Saídas do L298N

| Borne | Ligação |
|---|---|
| OUT1 | Primeiro terminal de ME1 e primeiro terminal de ME2 |
| OUT2 | Outro terminal de ME1 e outro terminal de ME2 |
| OUT3 | Primeiro terminal de MD1 e primeiro terminal de MD2 |
| OUT4 | Outro terminal de MD1 e outro terminal de MD2 |

OUT2 e OUT4 **não** são GND permanente. Não interligar as saídas dos canais A e B.

## Jumpers do L298N nesta configuração

| Jumper | Posição | Motivo |
|---|---|---|
| ENA | Removido | Receber PWM do pino D3 |
| ENB | Removido | Receber PWM do pino D11 |
| 5V-EN | Removido (lógica externa) | Receber 5 V do Arduino no borne lógico 5V |

Confirmar a função dos jumpers e bornes na placa real antes de ligar (ver
[ficha do L298N](../datasheet/componentes/l298n.md)).

## Observações

- A0 a A3 são usados como **entradas e saídas digitais**.
- A biblioteca Servo usa o **Timer1** no Uno (por isso não há PWM de motor em D9 e D10). O PWM dos
  motores fica em **D3 e D11**, ligados ao **Timer2**.
- D2 é a interrupção externa **INT0**; o firmware autônomo usa isso para frear assim que o IR muda.
- O código considera **IR em nível baixo = obstáculo**. Confirmar no módulo real (T03 e
  [caracterização](../datasheet/firmware/caracterizacao_sensores/caracterizacao_sensores.ino)).
- O ECHO do HC-SR04 é compatível com os 5 V do Uno; esta tabela não vale automaticamente para
  placas de 3,3 V.

## Identificação dos conjuntos

| Identificação | Posição e função |
|---|---|
| ME1 e ME2 | Motores dianteiro e traseiro do lado esquerdo (canal A) |
| MD1 e MD2 | Motores dianteiro e traseiro do lado direito (canal B) |
| SV1 e SV2 | Servos dos ultrassônicos esquerdo e direito |
| US1 e US2 | Ultrassônicos sobre os servos |
| IR | Sensor frontal fixo |
| S1 e S2 | Chaves de alimentação da lógica e dos motores |
