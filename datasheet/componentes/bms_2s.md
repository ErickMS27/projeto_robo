# BMS 2S

**No projeto:** proteção do pack de duas células em série. A saída protegida P+ / P- alimenta toda
a distribuição; P- é o ponto comum de retorno. O manual não especifica o modelo: a sequência de
ligação, a ativação e o balanceamento seguem o fabricante do BMS escolhido.

## Modelo instalado

| Campo | Valor |
|---|---|
| Fabricante / modelo / marcação | |
| Química suportada | |
| Datasheet ou manual usado | |
| Responsável pela ficha | |

## Dados do fabricante (preencher)

| Parâmetro | Valor | Fonte |
|---|---|---|
| Corrente contínua de descarga | | |
| Proteção de sobrecorrente / curto | | |
| Corte por sobrecarga (por célula) | | |
| Corte por descarga excessiva (por célula) | | |
| Balanceamento (sim/não) | | |
| Chaveamento no negativo (P- separado de B-) | | |
| Porta de carga separada (C-) | | |
| Sequência de ligação recomendada | | |

## Terminais

| Terminal usual | Função | Posição na placa instalada |
|---|---|---|
| B- | Extremidade negativa do conjunto de células | |
| BM ou B1 | Junção entre o positivo da 1ª célula e o negativo da 2ª | |
| B+ | Extremidade positiva do conjunto de células | |
| P+ e P- | Saída protegida para a distribuição do carrinho | |
| C- (quando presente) | Porta de carga separada | |

Alguns módulos compartilham B+ e P+; outros têm portas de carga e descarga distintas.

## Uso neste projeto

- BM é ponto de supervisão: **não** alimenta nenhuma parte do carrinho.
- Carga ligada direto em B- pode contornar a proteção.
- O BMS, as chaves, os conectores e os cabos precisam atender à demanda simultânea dos quatro
  motores e dos demais ramos (ver [dimensionamento](../dimensionamento.md)).
- A partida simultânea dos motores pode acionar a proteção de sobrecorrente: observar no T07.
- O BMS não é carregador.

## Confirmar no componente real

- [ ] Compatibilidade com a química das células
- [ ] Corrente de descarga acima da demanda total do carrinho
- [ ] P+ e P- identificados por medição
- [ ] Comportamento durante as partidas repetidas (T07)
- [ ] Carregador compatível com a química e o arranjo 2S
