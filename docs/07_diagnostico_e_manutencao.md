# Diagnóstico de falhas e manutenção

Seção 13 do manual.

| Sintoma | Verificação inicial | Encaminhamento |
|---|---|---|
| Uno reinicia ao acelerar | VIN sob carga, GND e estado do pack | Investigar queda na alimentação, retorno de corrente e contatos |
| Servos tremem ou perdem força | Tensão junto aos servos e folga mecânica | Rever conversor, cabos, esforço e limites de posição |
| Um lado não gira | ENA ou ENB, lógica de 5 V, alimentação VS e bornes | Confirmar jumpers e sinais; ensaiar o motor individualmente |
| Rodas do mesmo lado se opõem | Sentido de cada motor com chassi suspenso | Corrigir a polaridade do motor correspondente e atualizar a etiqueta |
| Carrinho faz curva ao avançar | Rodas, atrito, distribuição de massa e diferenças de motor | Corrigir a mecânica e calibrar o comando (`AJUSTE_PWM_*` no config.h); avaliar realimentação para maior precisão |
| Distância aparece como zero | TRIG, ECHO, GND e alvo de ensaio | Tratar como leitura inválida e investigar ausência de eco ou timeout |
| IR indica estado invertido | Saída do módulo diante de um alvo | Ajustar a convenção do programa ao módulo real (`IR_NIVEL_OBSTACULO`) |
| L298N aquece ou o BMS corta | Corrente dos pares e travamento mecânico | Rever dimensionamento; não contornar a proteção para manter o ensaio |
| Tinkercad não inicia com quatro motores | Comparar com a cópia de dois motores | Seguir o [registro da simulação](../programacao/simulacao_tinkercad.md) e evitar conclusões sobre a potência física |

## Manutenção de rotina

**Antes de cada uso**

- [ ] Aperto dos bornes
- [ ] Fixação das baterias
- [ ] Isolamento e passagem dos cabos
- [ ] Rodas e eixos livres de material que aumente o atrito

**Após cada ensaio**

- [ ] Registrar aquecimento, atuação das proteções e alterações de montagem

**Para manutenção**

- Retirar o pack **e** o cabo USB. S1 aberta não garante o Arduino sem alimentação com o USB conectado.
- Substituir componentes danificados e repetir os testes afetados pela intervenção.

## Registro das alterações

Registrar a versão do programa, as inversões de fios, o modelo dos módulos e as medições. Se a
pinagem mudar, atualizar ao mesmo tempo a [pinagem](../docs/pinagem.md), os programas e a
identificação dos chicotes.
