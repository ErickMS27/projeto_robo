# Motores CC (ME1, ME2, MD1, MD2)

**No projeto:** tração por lado. ME1 e ME2 em paralelo no canal A; MD1 e MD2 em paralelo no canal B.
**Referência:** [8] Dois motores por canal (Pololu) ([referencias.md](../referencias.md)). O manual
não especifica o modelo: preferir os dados do fabricante e completar com medição.

## Modelo instalado

| Campo | Valor |
|---|---|
| Fabricante / modelo | |
| Redução | |
| Diâmetro da roda | |
| Datasheet usado | |
| Responsável pela ficha | |

## Dados do fabricante (preencher)

| Parâmetro | Valor | Fonte |
|---|---|---|
| Tensão nominal | | |
| Corrente em vazio | | |
| Corrente de trabalho | | |
| Corrente de travamento (stall) | | |
| Rotação em vazio | | |
| Torque | | |

## Medições

Medir com o chassi suspenso, com amperímetro **em série** e, se possível, fonte de bancada com
limite de corrente. A corrente de partida pode não aparecer no visor de um multímetro comum. Se for
preciso medir o travamento, fazê-lo por no máximo 1 s, com corrente limitada na fonte.

| Motor | Corrente livre PWM 150 | Corrente livre PWM 255 | Corrente de partida | Sentido conferido |
|---|---|---|---|---|
| ME1 | | | | |
| ME2 | | | | |
| MD1 | | | | |
| MD2 | | | | |
| Par esquerdo | | | | |
| Par direito | | | | |

## Uso neste projeto

- A corrente do canal é a soma dos dois motores: comparar com a capacidade do
  [L298N](l298n.md), considerando partida e travamento.
- Sem encoders, o mesmo PWM não garante rotações iguais: diferenças entre motores, atrito e carga
  desviam a trajetória (correção por `AJUSTE_PWM_*` no `config.h`).
- Tensão média aproximada nos motores: ver [dimensionamento](../dimensionamento.md), item 4.

## Confirmar no componente real

- [ ] Tensão nominal compatível com a tensão efetiva entregue pela ponte
- [ ] Corrente por canal dentro do limite do módulo
- [ ] Rotação semelhante entre os quatro motores
