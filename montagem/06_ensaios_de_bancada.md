# Ensaios de bancada

Seção 11 do manual. Realizar na ordem, registrando no
[modelo do Apêndice B](registros/MODELO_registro_de_ensaios.md). Manter as rodas suspensas até
concluir a conferência de sentido e de corrente. Aprovar uma etapa permite avançar para a próxima;
não substitui a verificação da montagem completa.

| Teste | Procedimento | Critério para avançar | Programa |
|---|---|---|---|
| T01 | Inspeção sem fontes: polaridade, bornes, isolamento, fixação e jumpers | Nenhuma ligação trocada, curto franco ou parte móvel obstruída | — |
| T02 | S1 ligada e S2 aberta; medir pack, VIN e saídas de 5 V | Tensões compatíveis com cada componente e ajuste correto do conversor | [teste_sensores](firmware/teste_sensores/teste_sensores.ino) (não aciona nada) |
| T03 | Ler IR e ultrassônicos no monitor serial em 9600 baud | IR responde à presença do alvo; distâncias respondem a um alvo conhecido | [teste_sensores](firmware/teste_sensores/teste_sensores.ino) |
| T04 | Centralizar os servos e ensaiar posições seguras individualmente | Curso livre, sem esforço no batente, sem reiniciar a placa e sem queda indevida de tensão | [teste_servos](firmware/teste_servos/teste_servos.ino) |
| T05 | Acionar um motor de cada vez, com programa de bancada apropriado | Rotação e sentido identificados; corrente compatível com o acionamento | [bancada_motores](firmware/bancada_motores/bancada_motores.ino) (`e`, `E`, `d`, `D`) |
| T06 | Acionar os dois motores de cada lado e depois os quatro juntos | Quatro rodas produzem avanço; alimentação e aquecimento permanecem admissíveis | [bancada_motores](firmware/bancada_motores/bancada_motores.ino) (`e`, `d`, `f`, `t`, `<`, `>`) |
| T07 | Repetir partidas e observar VIN, 5 V dos servos e comportamento do BMS | Sem reinicialização, corte inesperado, perda de torque ou conexão aquecida | [bancada_motores](firmware/bancada_motores/bancada_motores.ino) (`r`) |
| T08 | Operar em piso controlado após os ensaios elétricos | Tração estável e condição de parada comprovada para o programa utilizado | [carrinho_autonomo](../programacao/firmware/carrinho_autonomo/carrinho_autonomo.ino) |

## Observações por ensaio

**T05 — um motor de cada vez.** Os dois motores de cada lado estão em paralelo no mesmo canal.
Para ensaiar um motor isolado, retirar as fontes e desconectar o outro motor do par. Conferir que,
no comando "frente", a roda gira no sentido de avanço do chassi.

**T06 — sentido.** Primeiro cada lado, depois os quatro juntos. Rodas do mesmo lado girando em
sentidos opostos indicam um motor com os fios invertidos. Registrar a correção em
[chicotes e etiquetas](05_chicotes_e_etiquetas.md).

**T07 — partidas repetidas.** O comando `r` faz 10 partidas de 1 s com 1 s de intervalo. Medir VIN
junto ao Uno e os 5 V junto aos servos durante as partidas.

**T08 — piso controlado.** Só depois de T01 a T07 aprovados. Área livre, sem degraus, com alguém
pronto para desligar S2. Testar primeiro a parada pelo IR e pelos ultrassônicos com o carrinho
suspenso. A ré é feita sem sensor traseiro.

## Condições de medição

- Medir as tensões **junto ao consumidor e ao seu retorno**, além da saída da fonte. Diferença
  relevante entre esses pontos indica perda nos cabos ou contatos.
- Corrente: instrumento e escala adequados, **em série**. Amperímetro entre positivo e negativo
  provoca curto.
- O [teste_conexoes](firmware/teste_conexoes/teste_conexoes.ino) aciona os dois lados juntos; para
  ensaios individuais usar o [bancada_motores](firmware/bancada_motores/bancada_motores.ino).
- Na avaliação dos servos, alterar as posições centrais apenas depois de conferir a folga mecânica.

## Interromper o ensaio

Retirar a energia diante de:

- inversão de polaridade;
- reinicialização repetida;
- aquecimento anormal;
- queda de tensão fora da especificação;
- roda travada;
- atuação inesperada do BMS.

Corrigir a causa e repetir a etapa afetada antes de prosseguir.
