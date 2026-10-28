# projeto_robo

Projeto Robô Arduino/Raspberry - NP2 Sistemas Autômatos

Carrinho robótico com **quatro motores CC** (dois por lado), **Arduino Uno**, ponte H **L298N**,
conversor **LM2596** para os servos e pack **2S de células 18650 com BMS**. Dois sensores
ultrassônicos **HC-SR04** ficam sobre servos e um **sensor IR** fixo indica obstáculo à frente.

Documento de referência: [Manual técnico ROB4M MT 001 — Revisão 1.0](docs/Manual_Tecnico_Carrinho_Quatro_Motores.pdf).

## Equipes

| Equipe | Integrantes | Pasta | Responsabilidade |
|---|---|---|---|
| **Montagem** | Kauan, Caio, Pedro, Kelvin, Eduardo, Erick Kelvin | [montagem/](montagem/) | Montagem mecânica e elétrica, chicotes, ensaios de bancada T01 a T08 e registro dos ensaios |
| **Programação** | Luiz, Gabriel, Guilherme, Erick | [programacao/](programacao/) | Firmware de navegação autônoma, parada de emergência e simulação no Tinkercad |
| **Datasheet** | Dimitri, Andrey, Luan, Pedro Henrique, Israel | [datasheet/](datasheet/) | Fichas técnicas, dimensionamento elétrico, caracterização dos sensores e referências |

Responsabilidades detalhadas e o que cada equipe entrega às outras: [docs/equipes.md](docs/equipes.md).

## Estrutura

```
projeto_robo/
├── docs/
│   ├── Manual_Tecnico_Carrinho_Quatro_Motores.pdf   manual ROB4M MT 001 Rev. 1.0
│   ├── equipes.md                                   integrantes, tarefas e entregas
│   └── pinagem.md                                   pinagem oficial (seção 7 do manual)
│
├── montagem/                                        equipe de Montagem
│   ├── 01_lista_de_materiais.md
│   ├── 02_distribuicao_de_energia.md
│   ├── 03_montagem_mecanica.md
│   ├── 04_montagem_eletrica.md
│   ├── 05_chicotes_e_etiquetas.md
│   ├── 06_ensaios_de_bancada.md
│   ├── 07_diagnostico_e_manutencao.md
│   ├── registros/MODELO_registro_de_ensaios.md      Apêndice B
│   └── firmware/
│       ├── teste_conexoes/      programa de teste do Apêndice A
│       ├── teste_sensores/      ensaio T03
│       ├── teste_servos/        ensaio T04
│       └── bancada_motores/     ensaios T05 a T07
│
├── programacao/                                     equipe de Programação
│   ├── simulacao_tinkercad.md
│   └── firmware/carrinho_autonomo/
│       ├── carrinho_autonomo.ino   máquina de estados e parada de emergência
│       ├── config.h                pinagem e parâmetros de calibração
│       ├── motores.h / motores.cpp
│       ├── sensores.h / sensores.cpp
│       └── servos.h / servos.cpp
│
└── datasheet/                                       equipe de Datasheet
    ├── componentes/             uma ficha técnica por componente
    ├── dimensionamento.md       correntes, tensões, autonomia e PWM
    ├── referencias.md           fontes técnicas do manual
    ├── pdfs/                    datasheets dos modelos instalados
    └── firmware/caracterizacao_sensores/
```

## Firmware

Todos os sketches usam **Arduino Uno**, **monitor serial em 9600 baud** e a biblioteca **Servo**
(já inclusa na IDE do Arduino). Cada pasta de sketch abre direto na IDE.

| Sketch | Equipe | Para que serve | Ensaio |
|---|---|---|---|
| [teste_conexoes](montagem/firmware/teste_conexoes/teste_conexoes.ino) | Montagem | Programa do Apêndice A, sem alterações: ciclo de 2 s ligado / 2 s desligado | Etapa 7 |
| [teste_sensores](montagem/firmware/teste_sensores/teste_sensores.ino) | Montagem | Leitura do IR e dos ultrassônicos, com motores desligados | T03 |
| [teste_servos](montagem/firmware/teste_servos/teste_servos.ino) | Montagem | Centralização e posições seguras dos servos | T04 |
| [bancada_motores](montagem/firmware/bancada_motores/bancada_motores.ino) | Montagem | Acionamento por lado, giro, frenagem e partidas repetidas | T05 a T07 |
| [carrinho_autonomo](programacao/firmware/carrinho_autonomo/carrinho_autonomo.ino) | Programação | Navegação com desvio de obstáculos e parada pelo IR | T08 |
| [caracterizacao_sensores](datasheet/firmware/caracterizacao_sensores/caracterizacao_sensores.ino) | Datasheet | Estatística dos ultrassônicos e nível ativo do IR | Fichas |

## Ordem de trabalho

1. **Datasheet** identifica os modelos realmente comprados (motores, servos, BMS, células, módulos)
   e confirma tensões, correntes e jumpers nas fichas de [datasheet/componentes/](datasheet/componentes/).
2. **Montagem** confere os materiais, monta sem energia e executa os ensaios T01 a T07 com o chassi
   suspenso, registrando tudo no modelo do Apêndice B.
3. **Programação** calibra o [config.h](programacao/firmware/carrinho_autonomo/config.h) com os
   resultados dos ensaios e só então libera o T08 em piso controlado.

## Segurança (resumo do manual)

- Montar e mudar cabos de potência ou jumpers **sem bateria e sem USB**.
- Manter **S2 desligada** ao carregar um programa.
- Manter **as rodas suspensas** até concluir a conferência de sentido e de corrente.
- **Não unir** o 5V do Arduino com o OUT+ do LM2596: os dois compartilham apenas o GND.
- Retirar a energia diante de inversão de polaridade, reinicialização repetida, aquecimento
  anormal, roda travada ou atuação inesperada do BMS.

## Fluxo no Git

- `main`: versões aprovadas em bancada. `dev`: integração entre as equipes.
- Cada equipe trabalha em branch própria criada a partir de `dev`, com o nome da equipe como
  prefixo (`montagem/...`, `programacao/...`, `datasheet/...`), e abre pull request para `dev`.
- Mudou a pinagem? Atualizar [docs/pinagem.md](docs/pinagem.md), **todos** os sketches e as
  etiquetas dos chicotes no mesmo pull request (seção 13 do manual).
