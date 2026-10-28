# Sensor IR frontal

**No projeto:** sensor fixo na frente do chassi, saída digital no D2, alimentado pelo 5V do Uno.
O manual não especifica o modelo: os dados devem vir da documentação do módulo comprado.

## Modelo instalado

| Campo | Valor |
|---|---|
| Fabricante / modelo / marcação | |
| Tipo de saída (push-pull, coletor aberto) | |
| Pull-up na placa (sim/não, valor) | |
| Ajuste de sensibilidade (trimpot) | |
| Datasheet usado | |
| Responsável pela ficha | |

## Dados do fabricante (preencher)

| Parâmetro | Valor | Fonte |
|---|---|---|
| Tensão de alimentação | | |
| Corrente | | |
| Distância de detecção | | |
| Nível da saída com obstáculo | | |

## Uso neste projeto

- O código interpreta **nível baixo como obstáculo** (`IR_NIVEL_OBSTACULO LOW`). Em muitos módulos
  de obstáculo a saída vai a LOW na detecção, mas isso precisa ser confirmado no módulo real.
- No Tinkercad o IR foi representado por um botão com pull-up de 10 kΩ. No módulo físico, verificar
  se o pull-up já existe ou se é necessário para o tipo de saída.
- No firmware autônomo, D2 é interrupção (INT0): uma mudança para o nível de obstáculo freia os
  motores na hora. Ruído na saída pode causar frenagens indevidas.

## Caracterização

Usar o [caracterizacao_sensores](../firmware/caracterizacao_sensores/caracterizacao_sensores.ino)
(comando `i`): iniciar sem alvo e depois aproximar e afastar um alvo.

| Nível em repouso | Nível com alvo | Transições espúrias sem alvo |
|---|---|---|
| | | |

| Alvo (cor / material) | Altura do sensor ao piso | Distância de detecção (cm) | Observação |
|---|---|---|---|
| | | | |
| | | | |

## Confirmar no componente real

- [ ] Nível ativo da saída (repassar à Programação)
- [ ] Necessidade de pull-up
- [ ] Distância de detecção com o piso e a altura reais
- [ ] Sensibilidade à luz ambiente
