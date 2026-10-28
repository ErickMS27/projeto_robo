# Equipe de Montagem

**Integrantes:** Kauan, Caio, Pedro, Kelvin, Eduardo, Erick Kelvin

Responsável pela montagem física com os **quatro motores** (ME1, ME2, MD1, MD2), pela distribuição
de energia, pelos chicotes e pelos ensaios de bancada T01 a T08. A distribuição das tarefas entre
os integrantes fica em [docs/equipes.md](../docs/equipes.md).

## Roteiro

| Ordem | Documento | Seções do manual |
|---|---|---|
| 1 | [Lista de materiais](01_lista_de_materiais.md) | 2 |
| 2 | [Distribuição de energia, BMS e jumpers](02_distribuicao_de_energia.md) | 3, 4 e 5 |
| 3 | [Montagem mecânica](03_montagem_mecanica.md) | 8 |
| 4 | [Montagem elétrica (etapas 1 a 7)](04_montagem_eletrica.md) | 6, 7 e 9 |
| 5 | [Chicotes e etiquetas](05_chicotes_e_etiquetas.md) | 2 e 8 |
| 6 | [Ensaios de bancada T01 a T08](06_ensaios_de_bancada.md) | 11 |
| 7 | [Diagnóstico e manutenção](07_diagnostico_e_manutencao.md) | 13 |

Pinagem de referência: [docs/pinagem.md](../docs/pinagem.md).

## Registro dos ensaios

Para cada sessão de ensaio, copiar [registros/MODELO_registro_de_ensaios.md](registros/MODELO_registro_de_ensaios.md)
para `registros/AAAA-MM-DD_descricao.md` e preencher. Valores observados no Tinkercad **não** vão
nos campos de medição do carrinho.

## Firmware de bancada

Abrir a pasta do sketch na IDE do Arduino, selecionar **Arduino Uno**, carregar com **S2 desligada**
e abrir o monitor serial em **9600 baud**.

| Sketch | Ensaio | O que faz |
|---|---|---|
| [teste_conexoes](firmware/teste_conexoes/teste_conexoes.ino) | Etapa 7 | Programa do Apêndice A: sensores no serial e ciclo de 2 s ligado / 2 s parado |
| [teste_sensores](firmware/teste_sensores/teste_sensores.ino) | T03 | IR e ultrassônicos no serial, motores desligados |
| [teste_servos](firmware/teste_servos/teste_servos.ino) | T04 | Centraliza e move cada servo dentro de limites seguros |
| [bancada_motores](firmware/bancada_motores/bancada_motores.ino) | T05 a T07 | Aciona cada lado, gira, freia e repete partidas; desliga sozinho após 3 s |

O firmware autônomo (T08) fica com a Programação:
[carrinho_autonomo](../programacao/firmware/carrinho_autonomo/carrinho_autonomo.ino).

## Regras de segurança

- Montar e alterar cabos de potência ou jumpers **com as fontes retiradas** (bateria e USB).
- **Nunca** medir resistência ou continuidade em circuito energizado.
- Manter as rodas suspensas até concluir a conferência de sentido e de corrente.
- Amperímetro sempre **em série**; ligado entre positivo e negativo provoca curto.
- S1 aberta não garante o Arduino sem alimentação se o USB continuar conectado.
- Não contornar a proteção do BMS para continuar um ensaio.
