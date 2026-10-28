# Lista de materiais

Seção 2 do manual. Conferir cada componente físico pela identificação da placa e pela documentação
do fabricante: o nome usado no simulador não substitui a especificação elétrica do componente
instalado. O modelo identificado deve ser repassado à equipe de Datasheet.

| Qtd | Componente | Verificação antes da montagem | Modelo identificado | Conferido |
|---|---|---|---|---|
| 1 | Arduino Uno R3 | Placa íntegra, porta USB e alimentação reconhecidas | | [ ] |
| 1 | Módulo L298N | Dois canais, bornes identificados, jumpers e dissipador conferidos | | [ ] |
| 4 | Motores CC com rodas | Tensão nominal e correntes de trabalho e de travamento identificadas | | [ ] |
| 2 | Servomotores | Tensão admissível, corrente de pico e curso mecânico conferidos | | [ ] |
| 2 | HC-SR04 | Pinos VCC, TRIG, ECHO e GND reconhecidos | | [ ] |
| 1 | Sensor IR frontal | Módulo com saída digital; confirmar polaridade ativa | | [ ] |
| 1 | Módulo LM2596 | Conversor ajustável com entrada e saída identificadas | | [ ] |
| 1 | BMS 2S | Modelo compatível com as células, corrente e terminais confirmados | | [ ] |
| 2 | Células 18650 | Química e especificações compatíveis; sem dano no invólucro | | [ ] |
| 1 | Suporte ou pack 2S | Associação em série e acesso à junção central quando exigido pelo BMS | | [ ] |
| 2 | Chaves S1 e S2 | Capacidade em corrente contínua adequada aos respectivos ramos | | [ ] |
| 1 | Chassi e fixadores | Suportes de motor, espaçadores, suportes de servo e rodas | | [ ] |
| Kit | Cabos e distribuição | Bornes, conectores polarizados e condutores dimensionados | | [ ] |
| Kit | Proteção e carga | Proteção de corrente dimensionada e carregador compatível com o pack | | [ ] |

## Instrumentos

- [ ] Multímetro
- [ ] Ferramentas de fixação
- [ ] Material para identificação dos cabos (etiquetas nas duas extremidades)
- [ ] Fonte de bancada com limite de corrente (facilita a investigação nos ensaios de alimentação)
- [ ] Instrumento com captura de pico para a corrente de partida, quando disponível
  (o visor de um multímetro comum pode não registrar o pico)

## Organização prévia

- [ ] Cabos de potência separados dos cabos de sinal
- [ ] Etiquetas ME1, ME2, MD1, MD2, SV1, SV2, US1 e US2 preparadas (ver [chicotes](05_chicotes_e_etiquetas.md))
- [ ] Protoboard reservada aos sinais e à distribuição de baixa corrente
