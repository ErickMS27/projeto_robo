# Montagem elétrica

Seções 6, 7 e 9 do manual. Executar a montagem **sem bateria e sem USB**. Toda mudança de cabo de
potência ou de jumper é feita com as fontes retiradas. A energização fica restrita às verificações
indicadas em cada etapa.

## Etapa 1 — Preparar o pack e a saída protegida

- [ ] Associação 2S, química das células e modelo do BMS confirmados (com a equipe de Datasheet)
- [ ] Pack conectado conforme a sequência do fabricante da proteção
- [ ] P+ e P- identificados **por medição** antes de conectar a carga
- [ ] Nenhuma sequência genérica aplicada a BMS sem identificação

## Etapa 2 — Distribuir a energia

- [ ] P+ levado ao elemento de proteção e às entradas de S1 e S2
- [ ] Saída de S1 ligada ao **VIN do Uno** e ao **IN+ do LM2596**
- [ ] Saída de S2 ligada à **entrada de potência do L298N**
- [ ] P- derivado ao distribuidor de GND e aos retornos dos módulos

## Etapa 3 — Ajustar o LM2596

- [ ] S2 aberta e servos desconectados
- [ ] IN- e OUT- do LM2596 ligados ao GND comum
- [ ] Somente o ramo S1 alimentado; OUT+ medido em relação a OUT-
- [ ] Saída ajustada para **5,0 V** e alimentação desligada
- [ ] VCC dos servos ligados a OUT+ e retornos ao GND comum
- [ ] Tensão admissível dos servos confirmada

## Etapa 4 — Conectar a lógica e os sinais

- [ ] Jumper **5V-EN removido** e 5V do Uno ligado ao borne lógico do L298N
- [ ] Jumpers **ENA e ENB removidos**
- [ ] Seis entradas de controle ligadas: D3→ENA, D4→IN1, D5→IN2, D6→IN3, D7→IN4, D11→ENB
- [ ] Sinais dos servos: D9→SV1, D10→SV2
- [ ] Sensores: D2→OUT do IR, A0→TRIG US1, A1→ECHO US1, A2→TRIG US2, A3→ECHO US2
- [ ] VCC de US1, US2 e IR no 5V do Uno; GND no ponto comum

Tabela completa: [docs/pinagem.md](../docs/pinagem.md).

## Etapa 5 — Conectar os quatro motores

Com todas as fontes retiradas:

| Borne | Ligação |
|---|---|
| OUT1 | Primeiro terminal de ME1 e primeiro terminal de ME2 |
| OUT2 | Outro terminal de ME1 e outro terminal de ME2 |
| OUT3 | Primeiro terminal de MD1 e primeiro terminal de MD2 |
| OUT4 | Outro terminal de MD1 e outro terminal de MD2 |

- [ ] Par esquerdo em OUT1/OUT2 e par direito em OUT3/OUT4
- [ ] Aperto, isolamento e identificação conferidos
- [ ] Saídas dos canais A e B **não** interligadas (OUT2 e OUT4 não são GND)

A ligação por cor é só uma referência inicial: o sentido é verificado com o chassi suspenso nos
ensaios T05 e T06. Motores em posições espelhadas podem exigir inversão dos dois fios de um motor.

## Etapa 6 — Conferência sem energia

- [ ] Polaridade de todas as alimentações
- [ ] Continuidade do GND comum
- [ ] Nenhum fio solto
- [ ] Posição dos jumpers conforme a etapa 4
- [ ] Nenhum curto franco entre os barramentos (capacitores podem dar indicação transitória no instrumento)

**Nunca medir resistência ou continuidade em circuito energizado.**

## Etapa 7 — Carregar e testar o programa

- [ ] **S2 desligada** durante a carga do programa
- [ ] Placa **Arduino Uno** selecionada; [teste_conexoes](firmware/teste_conexoes/teste_conexoes.ino) carregado
- [ ] Monitor serial aberto em **9600 baud**
- [ ] Chassi suspenso e lógica verificada
- [ ] Ensaios da [seção 11](06_ensaios_de_bancada.md) executados **antes** de as rodas tocarem o piso
