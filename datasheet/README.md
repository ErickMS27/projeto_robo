# Equipe de Datasheet

**Integrantes:** Dimitri, Andrey, Luan, Pedro Henrique, Israel

Responsável por levantar e documentar as especificações dos componentes **efetivamente instalados**,
fazer o dimensionamento elétrico e caracterizar os sensores. O manual reforça que o nome de um
componente no simulador não substitui a especificação elétrica do componente real. A divisão das
fichas entre os integrantes fica em [docs/equipes.md](../docs/equipes.md).

## Fichas técnicas

| Componente | Ficha | Referência do manual |
|---|---|---|
| Arduino Uno R3 | [arduino_uno_r3.md](componentes/arduino_uno_r3.md) | [1], [5], [7], [10] |
| Ponte H L298N | [l298n.md](componentes/l298n.md) | [2], [3], [8] |
| Conversor LM2596 | [lm2596.md](componentes/lm2596.md) | [4] |
| Ultrassônico HC-SR04 | [hc_sr04.md](componentes/hc_sr04.md) | [6] |
| Servomotores | [servomotor.md](componentes/servomotor.md) | [7] |
| Sensor IR | [sensor_ir.md](componentes/sensor_ir.md) | — |
| Motores CC | [motor_cc.md](componentes/motor_cc.md) | [8] |
| BMS 2S | [bms_2s.md](componentes/bms_2s.md) | — |
| Células 18650 | [celula_18650.md](componentes/celula_18650.md) | — |

Também: [dimensionamento elétrico](dimensionamento.md) e [referências técnicas](referencias.md).

## Como preencher uma ficha

1. Pegar com a Montagem o modelo e a marcação de cada componente
   ([lista de materiais](../montagem/01_lista_de_materiais.md)).
2. Baixar o datasheet do fabricante desse modelo e salvar em [pdfs/](pdfs/).
3. Preencher a seção **Modelo instalado** e conferir os **Dados de referência**, corrigindo o que
   for diferente no modelo real.
4. Marcar os itens de **Confirmar no componente real** e anotar a fonte de cada valor.

Ordem de confiança das fontes: **datasheet do fabricante do modelo instalado** > **medição em
bancada** > referência genérica. Sempre indicar de onde veio o número. Valores observados no
Tinkercad não são especificação.

## Caracterização dos sensores

O sketch [caracterizacao_sensores](firmware/caracterizacao_sensores/caracterizacao_sensores.ino)
gera os dados das fichas do HC-SR04 e do IR:

- `u`: 50 leituras de cada ultrassônico com média, mínimo, máximo e desvio padrão;
- `r`: as mesmas leituras em CSV para planilha;
- `i`: nível do IR em repouso e transições com alvo, para confirmar o nível ativo.

## Entregas

| Para | O quê |
|---|---|
| Montagem | Tensões admissíveis, posição dos jumpers do módulo real, sequência de ligação do BMS, carregador compatível, corrente dos motores por canal |
| Programação | Nível ativo do IR, faixa útil e dispersão dos ultrassônicos, curso admissível dos servos |
