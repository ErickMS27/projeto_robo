# Dimensionamento elétrico

Fórmulas e critérios da seção 4 e da seção 5 do manual. Os números marcados como **exemplo** só
ilustram o cálculo: substituir pelos dados das fichas e pelas medições da Montagem.

## 1. Tensões do pack 2S

| Química | Pack nominal | Pack cheio | Observação |
|---|---|---|---|
| Li-ion 3,7 V | 7,4 V | 8,4 V | Referência do manual |
| LiFePO4 3,2 V | 6,4 V | 7,2 a 7,3 V | Abaixo da faixa recomendada do VIN |

A tensão mínima depende do corte por descarga do BMS e das células (ver
[bms_2s.md](componentes/bms_2s.md) e [celula_18650.md](componentes/celula_18650.md)).

## 2. Margem do VIN do Uno

Faixa recomendada: **7 a 12 V** [5]. Com Li-ion 2S, o pack sai dessa faixa abaixo de
**3,5 V por célula** (7,0 V no pack), antes ainda de descontar as quedas em S1, cabos e contatos
durante a partida dos motores.

| Ponto | Sem acionamento | Durante partida |
|---|---|---|
| Pack (P+ / P-) | | |
| VIN junto ao Uno | | |
| Diferença (perda no ramo S1) | | |

## 3. Corrente por canal da ponte H

```
I_canal_A = I_ME1 + I_ME2
I_canal_B = I_MD1 + I_MD2
```

Calcular para três situações e comparar com a capacidade do **módulo** (não só do CI L298, que
indica 2 A contínuos por canal [2]):

| Situação | Canal A | Canal B | Dentro do limite? |
|---|---|---|---|
| Rodas livres | | | |
| Partida | | | |
| Travamento | | | |

Se o conjunto exceder a capacidade térmica ou elétrica do módulo, reduzir a carga ou escolher um
acionamento dimensionado para ela.

## 4. Tensão média nos motores

```
V_motor ≈ (V_pack − V_queda_ponte) × PWM / 255
```

**Exemplo** com a queda típica de 1,8 V a 1 A do L298 [2]:

| Pack | PWM | V_motor aproximada |
|---|---|---|
| 7,4 V | 150 | (7,4 − 1,8) × 0,588 ≈ **3,3 V** |
| 8,4 V | 150 | (8,4 − 1,8) × 0,588 ≈ **3,9 V** |
| 7,4 V | 255 | 7,4 − 1,8 ≈ **5,6 V** |

A queda varia com a corrente e a temperatura (com dois motores por canal a corrente pode passar de
1 A). PWM 150 é 58,8 % da escala, **não** 58,8 % da rotação máxima. Comparar com a tensão nominal
dos [motores](componentes/motor_cc.md).

## 5. Corrente dos servos vista pelo pack

```
I_pack_servos = (5 V × I_servos) / (V_pack × η)
```

η é o rendimento do LM2596 medido na [ficha](componentes/lm2596.md).

**Exemplo:** servos consumindo 1,0 A juntos, pack em 7,4 V, η = 0,85:
5 × 1,0 / (7,4 × 0,85) ≈ **0,79 A** no pack.

## 6. Corrente total e proteção

```
I_S2   = I_canal_A + I_canal_B
I_S1   = I_Uno_sensores_lógica + I_pack_servos
I_pack = I_S1 + I_S2
```

| Ramo | Regime | Pico (partida) | Fonte do valor |
|---|---|---|---|
| S2 (motores) | | | |
| S1 (lógica + servos) | | | |
| Pack total | | | |

O BMS, as chaves S1 e S2, os conectores, os cabos e o elemento de proteção precisam atender à
demanda simultânea dos quatro motores e dos demais ramos [8].

| Item | Capacidade | Demanda máxima | OK? |
|---|---|---|---|
| BMS (descarga contínua) | | | |
| Chave S1 | | | |
| Chave S2 | | | |
| Elemento de proteção | | | |
| Cabos de potência | | | |

## 7. Autonomia

Estimativa inicial:

```
t (h) ≈ C (Ah) × fração utilizável / I_média (A)
```

**Exemplo:** 2,0 Ah × 0,8 / 1,5 A ≈ 1,07 h (≈ 64 min).

O manual exige que a autonomia seja obtida **por medição** no carrinho montado, com sua massa e o
piso de operação: partir do pack cheio e anotar o tempo até o corte do BMS ou até VIN sair da faixa.

| Data | Pack inicial | Programa | Piso | Tempo até o fim | Motivo do fim |
|---|---|---|---|---|---|
| | | | | | |

## 8. Ultrassom

```
distância (cm) = tempo_eco (µs) × 0,034 / 2
velocidade do som ≈ 331,3 + 0,606 × T (m/s), T em °C
```

- Timeout de 30 ms: 30 000 × 0,034 / 2 = **510 cm**, acima do alcance de 4 m [6].
- A 20 °C o som anda a ≈ 343 m/s (0,0343 cm/µs): o fator 0,034 do código subestima a distância
  em cerca de 1 %. Diferença pequena para as distâncias de parada usadas.

## 9. PWM

- `analogWrite(pino, 150)` → 150 / 255 = **58,8 %** de ciclo ativo.
- D3 e D11 usam o Timer2, com PWM de ≈ 490 Hz [10].
