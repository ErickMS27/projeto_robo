# Ultrassônico HC-SR04

**No projeto:** US1 (esquerdo, TRIG A0 / ECHO A1) e US2 (direito, TRIG A2 / ECHO A3), montados
sobre SV1 e SV2.
**Referência:** [6] Datasheet do HC-SR04 (ElecFreaks) ([referencias.md](../referencias.md)).

## Modelo instalado

| Campo | US1 | US2 |
|---|---|---|
| Fabricante / marcação | | |
| Datasheet usado | | |
| Responsável pela ficha | | |

## Dados de referência

| Parâmetro | Valor | Fonte |
|---|---|---|
| Alimentação | 5 V DC | [6] |
| Corrente de trabalho | 15 mA | [6] |
| Ultrassom | Rajada de 8 ciclos a 40 kHz | [6] |
| Alcance | 2 cm a 4 m | [6] |
| Ângulo de medição | 15° | [6] |
| Disparo | Pulso TTL de 10 µs em TRIG | [6] |
| Saída | Pulso em ECHO com largura proporcional à distância | [6] |
| Conversão | distância (cm) = tempo (µs) / 58 | [6] |
| Ciclo de medição sugerido | Acima de 60 ms | [6] |

## Uso neste projeto

- O código usa `distância = tempo × 0,034 / 2` (velocidade do som ≈ 340 m/s), equivalente a
  tempo / 58,8.
- `pulseIn` espera o eco por até **30 ms** (≈ 510 cm, acima do alcance). Sem eco, retorna 0: isso é
  **ausência de leitura válida**, não distância zero.
- O firmware autônomo considera válidas leituras entre 2 e 400 cm e alterna US1 e US2 para reduzir
  ecos cruzados.
- O ECHO é compatível com a lógica de 5 V do Uno; não vale automaticamente para placas de 3,3 V.

## Caracterização

Usar o [caracterizacao_sensores](../firmware/caracterizacao_sensores/caracterizacao_sensores.ino)
(comando `u`) com um alvo plano e rígido, perpendicular ao sensor.

| Alvo (cm) | US1 média | US1 desvio | US1 válidas | US2 média | US2 desvio | US2 válidas |
|---|---|---|---|---|---|---|
| 10 | | | /50 | | | /50 |
| 20 | | | /50 | | | /50 |
| 50 | | | /50 | | | /50 |
| 100 | | | /50 | | | /50 |
| 200 | | | /50 | | | /50 |

Registrar também a temperatura ambiente e observações sobre alvos macios, estreitos ou inclinados.

## Confirmar no componente real

- [ ] Pinos VCC, TRIG, ECHO e GND identificados
- [ ] Faixa útil e dispersão nas distâncias de parada (20 cm) e cautela (45 cm) do firmware
- [ ] Interferência entre US1 e US2 quando os dois olham para a frente
- [ ] Taxa de leituras sem eco em um ambiente típico de operação
