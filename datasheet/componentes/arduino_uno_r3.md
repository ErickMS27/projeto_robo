# Arduino Uno R3

**No projeto:** controlador do carrinho, alimentado por VIN a partir de S1.
**Referências:** [1] Documentação da placa, [5] Fontes de alimentação, [7] Timers da biblioteca
Servo, [10] Pinos e temporizadores de PWM ([referencias.md](../referencias.md)).

## Modelo instalado

| Campo | Valor |
|---|---|
| Fabricante / versão da placa | |
| Original ou compatível (chip USB) | |
| Datasheet usado | |
| Responsável pela ficha | |

## Dados de referência

| Parâmetro | Valor | Fonte |
|---|---|---|
| Microcontrolador | ATmega328P, 16 MHz | [1] |
| Tensão de operação | 5 V | [1] |
| Tensão em VIN recomendada | 7 a 12 V | [5] |
| I/O digitais | 14, dos quais 6 com PWM (3, 5, 6, 9, 10, 11) | [1] |
| Entradas analógicas | 6 (A0 a A5), utilizáveis como I/O digital | [1] |
| Corrente DC por pino de I/O | 20 mA | [1] |
| Memória | 32 KB flash (0,5 KB do bootloader), 2 KB SRAM, 1 KB EEPROM | [1] |
| Interrupções externas | D2 (INT0) e D3 (INT1) | [1] |
| PWM e temporizadores | Timer0: D5, D6 (≈ 980 Hz). Timer1: D9, D10. Timer2: D3, D11 (≈ 490 Hz) | [10] |
| Biblioteca Servo no Uno | Usa o Timer1: desativa `analogWrite` em D9 e D10 | [7] |

## Uso neste projeto

- PWM dos motores em **D3 e D11** (Timer2), compatível com os servos em D9 e D10 (Timer1).
- D2 recebe o IR e é usado como interrupção INT0 no firmware autônomo.
- A0 a A3 funcionam como I/O digital (TRIG e ECHO dos ultrassônicos).
- O pino **5V** alimenta US1, US2, IR e a lógica do L298N. Quando a placa é alimentada por VIN,
  esses 5 V vêm do regulador da placa: manter apenas cargas de baixa corrente nesse pino.
- A Montagem mede VIN durante a partida dos motores (T02 e T07).

## Margem de alimentação com pack 2S

| Condição do pack | Tensão aproximada do pack | Situação em VIN |
|---|---|---|
| Li-ion cheio | 8,4 V | Dentro da faixa recomendada |
| Li-ion nominal | 7,4 V | Dentro, com pouca margem |
| Li-ion abaixo de 3,5 V/célula | < 7,0 V | Abaixo da faixa recomendada |
| LiFePO4 nominal | 6,4 V | Abaixo da faixa recomendada |

Quedas em S1, cabos e contatos reduzem ainda mais a tensão em VIN. Ver
[dimensionamento](../dimensionamento.md).

## Confirmar no componente real

- [ ] Versão da placa e regulador presente
- [ ] VIN medido junto ao Uno, sem e com motores acionados
- [ ] Ausência de reinicialização durante partidas (T07)
- [ ] Soma das correntes no pino 5V (sensores + lógica do L298N)
