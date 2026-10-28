# Simulação no Tinkercad

Seção 12 do manual.

## Erro observado

No circuito com quatro motores, o Tinkercad mostrou **"Erro de início de simulação"** seguido de
**"Desculpe, mas este circuito não pode ser simulado"**. Os testes foram feitos em uma cópia,
preservando o projeto original com quatro motores e o mesmo programa de teste.

| Configuração ensaiada | Resultado observado |
|---|---|
| Quatro motores, dois em paralelo por lado | Erro de inicialização reproduzido |
| Quatro motores com o LM7805 retirado | O mesmo erro persistiu |
| Sem os quatro motores | A simulação iniciou; servos centralizaram e os sensores enviaram leituras |
| Dois motores, um por lado | A simulação iniciou e os motores giraram; rotações próximas de 100 RPM, incluindo 102 RPM nos dois |
| Três motores com um par em paralelo | O erro reapareceu; o resultado se repetiu ao colocar o par no outro lado |
| Resistência em série nos motores adicionais | Os ensaios com 1 Ω e 100 Ω não eliminaram o erro; os resistores foram retirados da cópia final |

## Conclusão sustentada pelos testes

- O gatilho reproduzível está associado aos **pares de motores de engrenagem em paralelo** nessa montagem.
- Com um motor por lado o mesmo programa roda e os comandos podem ser observados.
- Não foi comprovada sobrecorrente como causa, nem uma proibição geral de quatro motores no Tinkercad.
- A falha da simulação **não invalida** a ligação física de dois motores por canal, desde que o driver
  suporte a corrente conjunta. O projeto de tração continua com ME1, ME2, MD1 e MD2.

## O que a cópia representa

| Montagem física | Representação no simulador | Limite do ensaio |
|---|---|---|
| Quatro motores CC | Dois motores, um por lado | Verifica comandos dos lados; não reproduz a corrente dos quatro motores |
| Módulo L298N | Componente L293D | Não valida as perdas nem a capacidade da ponte real |
| Módulo LM2596 | Regulador LM7805 | Não reproduz o comportamento do conversor chaveado real |
| Pack 2S com BMS | Fontes de pilhas em série | Não verifica proteção, carga, balanceamento ou autonomia |
| Sensor IR digital | Botão com pull-up de 10 kΩ | Representa o nível lógico; não testa alcance nem ambiente |

Na cópia, a saída do regulador ficou perto de 4,93 V sem motores e chegou a 2,25 V durante a
execução com dois motores. Essas leituras pertencem ao modelo com LM7805 e não provam o comportamento
do LM2596 físico.

## Como reproduzir

- Cópia: [Robo diagnostico com 2 motores](https://www.tinkercad.com/things/iRuOsUpIP9L/editel)
  (o acesso depende das permissões da conta).
- Conferir as chaves e o estado das fontes: o Arduino pode continuar ativo por USB no simulador.
- Observar a rotação na fase de 2 s de movimento e as mensagens no monitor serial.
- Para novas modificações, trabalhar em **outra cópia** e registrar **uma alteração por teste**.

## Simular o firmware autônomo

O [carrinho_autonomo](firmware/carrinho_autonomo/) pode ser levado para a cópia com dois motores
para conferir a lógica dos estados. Se o editor de código aceitar apenas um arquivo, colar o
conteúdo nesta ordem e apagar as linhas `#include "..."` dos arquivos locais (as de `<Arduino.h>` e
`<Servo.h>` podem ficar):

1. `config.h`
2. `motores.h`, `sensores.h`, `servos.h`
3. `motores.cpp`, `sensores.cpp`, `servos.cpp`
4. `carrinho_autonomo.ino`

Para o IR, o botão com pull-up gera LOW ao ser pressionado, que corresponde a `IR_NIVEL_OBSTACULO LOW`.
