# Montagem mecânica e organização

Seção 8 do manual.

## Fixação dos módulos

- [ ] Acesso livre às chaves S1 e S2, ao conector USB, aos bornes e ao ajuste do LM2596
- [ ] Módulos instalados sobre espaçadores
- [ ] Nenhum contato entre a face inferior das placas e partes condutivas do chassi

## Tração e distribuição de massa

- [ ] ME1, ME2, MD1 e MD2 fixados nos suportes
- [ ] Rodas girando livremente **antes** de instalar os chicotes
- [ ] Baterias posicionadas de forma firme e equilibrada
- [ ] Cabos, abraçadeiras e parafusos longe dos eixos, das rodas e dos mecanismos dos servos

## Sensores e servos

1. [ ] Com o chassi suspenso e **S2 desligada**, carregar o
   [teste_servos](firmware/teste_servos/teste_servos.ino) para centralizar os servos em 90°.
2. [ ] Só depois ajustar os braços e fixar US1 e US2 na orientação frontal de referência
   (a posição elétrica de 90° não garante o alinhamento se o braço foi montado fora de posição).
3. [ ] Conferir o curso útil de cada conjunto **sem forçar os batentes**.
4. [ ] Deixar folga no cabo dos ultrassônicos para o movimento dos servos.
5. [ ] Fixar o sensor IR à frente, sem obstrução pelo chassi. A distância e a altura de detecção
   dependem do módulo e do piso.

## Chicotes

- [ ] Cabos de motor separados dos fios TRIG, ECHO e dos sinais dos servos
- [ ] Conexões de potência com retenção mecânica e retorno próprio ao distribuidor
- [ ] Etiquetas nas duas extremidades de cada chicote
- [ ] Qualquer inversão feita para corrigir o sentido de uma roda registrada em
  [chicotes e etiquetas](05_chicotes_e_etiquetas.md)
