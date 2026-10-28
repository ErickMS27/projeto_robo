# Servomotores SV1 e SV2

**No projeto:** orientam os ultrassônicos. SV1 (esquerdo) no D9 e SV2 (direito) no D10,
alimentados pelos 5,0 V do LM2596.
**Referência:** [7] Biblioteca Servo — timers AVR ([referencias.md](../referencias.md)). O manual
não especifica o modelo: os dados elétricos devem vir do datasheet do servo comprado.

## Modelo instalado

| Campo | SV1 | SV2 |
|---|---|---|
| Fabricante / modelo | | |
| Engrenagens (plástico / metal) | | |
| Datasheet usado | | |
| Responsável pela ficha | | |

## Dados do fabricante (preencher)

| Parâmetro | Valor | Fonte |
|---|---|---|
| Faixa de tensão de operação | | |
| Corrente em vazio | | |
| Corrente de pico / travamento | | |
| Torque | | |
| Curso mecânico | | |
| Largura de pulso mínima / máxima | | |

## Biblioteca Servo (Arduino)

| Item | Valor | Fonte |
|---|---|---|
| `write(ângulo)` | Converte 0 a 180° em pulsos entre 544 µs e 2400 µs (padrão da biblioteca) | [7] |
| Ajuste fino | `writeMicroseconds()` ou `attach(pino, min, max)` | [7] |
| Temporizador no Uno | Timer1 (sem PWM em D9 e D10 enquanto houver servo) | [7] |

O curso real para os mesmos pulsos varia entre modelos: comparar com o datasheet do servo instalado.

## Uso neste projeto

- Centralização em 90° na inicialização e para o ajuste mecânico dos braços.
- [teste_servos](../../montagem/firmware/teste_servos/teste_servos.ino): limites seguros iniciais de 45° a 135°.
- Firmware autônomo: varredura em 135° (SV1) e 45° (SV2), ajustável no `config.h`.

## Confirmar no componente real

- [ ] 5,0 V dentro da faixa admissível do servo
- [ ] Corrente de pico dos dois servos juntos compatível com o módulo LM2596
- [ ] Curso livre sem esforço no batente (T04)
- [ ] Sentido de giro para ângulos maiores (informar à Programação)
