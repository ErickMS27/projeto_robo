# Células 18650

**No projeto:** duas células em série (2S) com BMS. O formato 18650 (18 mm × 65 mm) **não define a
química** da célula: as tensões do pack dependem da especificação efetiva das células compradas.

## Células instaladas

| Campo | Célula 1 | Célula 2 |
|---|---|---|
| Marca / modelo | | |
| Química | | |
| Capacidade nominal (mAh) | | |
| Corrente máxima de descarga contínua | | |
| Tensão máxima de carga | | |
| Tensão mínima de descarga | | |
| Tensão medida ao receber | | |
| Datasheet usado | | |

Responsável pela ficha:

## Tensões típicas por química

Valores usuais para orientação; o que vale é o datasheet da célula instalada.

| Química | Nominal por célula | Carga máxima por célula | Pack 2S nominal | Pack 2S cheio |
|---|---|---|---|---|
| Li-ion (LCO, NMC, NCA) | 3,6 a 3,7 V | 4,2 V | 7,2 a 7,4 V | 8,4 V |
| LiFePO4 | 3,2 V | 3,6 a 3,65 V | 6,4 V | 7,2 a 7,3 V |

Com LiFePO4, o pack 2S fica abaixo da faixa recomendada para o VIN do Uno (7 a 12 V). Ver
[ficha do Arduino](arduino_uno_r3.md).

## Uso neste projeto

- Usar células compatíveis entre si (mesmo modelo e estado de carga semelhante) e suporte
  efetivamente ligado em série.
- Medir a tensão de cada célula e do conjunto antes de alimentar a distribuição.
- Carregar somente com carregador apropriado à química e ao arranjo 2S.
- A autonomia deve ser obtida por medição no carrinho montado ([dimensionamento](../dimensionamento.md)).

## Confirmar no componente real

- [ ] Química confirmada pelo datasheet
- [ ] Invólucro sem dano
- [ ] Diferença de tensão entre as células antes de ligar em série
- [ ] Corrente de descarga das células acima da demanda total do carrinho
