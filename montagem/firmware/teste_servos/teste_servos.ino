/*
 * ROB4M - Teste dos servos (ensaio T04)
 *
 * Centraliza SV1 e SV2 em 90 graus e permite ensaiar posições de cada servo
 * pelo monitor serial, sempre dentro de ANGULO_MIN e ANGULO_MAX. Os motores
 * ficam desligados.
 *
 * Executar com o chassi suspenso e S2 desligada (seção 8 do manual):
 *   1. Ligar e deixar os servos centralizarem.
 *   2. Só então ajustar os braços e fixar os sensores na orientação frontal.
 *   3. Conferir o curso útil sem forçar os batentes. Ampliar ANGULO_MIN e
 *      ANGULO_MAX somente depois de conferir a folga mecânica.
 *   4. Anotar para que lado cada servo gira com o ângulo maior: a Programação
 *      usa isso nos ângulos de varredura do config.h.
 *
 * Critério do T04: curso livre, sem esforço no batente, sem reiniciar a placa
 * e sem queda indevida de tensão.
 *
 * Comandos (monitor serial 9600 baud):
 *   c      centraliza os dois servos
 *   q / a  SV1 (esquerdo) +PASSO_GRAUS / -PASSO_GRAUS
 *   w / s  SV2 (direito)  +PASSO_GRAUS / -PASSO_GRAUS
 *   v      varredura lenta dos dois servos entre os limites
 *   ?      mostra os comandos
 */

#include <Servo.h>

// Pinos da ponte H (mantidos desligados)
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 11

// Pinos dos servos
#define SERVO_ESQ_PIN 9
#define SERVO_DIR_PIN 10

#define ANGULO_CENTRO 90
#define ANGULO_MIN 45
#define ANGULO_MAX 135
#define PASSO_GRAUS 5
// Tempo por grau na varredura
#define ATRASO_VARREDURA_MS 20

Servo servoEsquerdo;
Servo servoDireito;

int anguloEsq = ANGULO_CENTRO;
int anguloDir = ANGULO_CENTRO;

void setup() {
  Serial.begin(9600);
  desligarPonteH();

  servoEsquerdo.attach(SERVO_ESQ_PIN);
  servoDireito.attach(SERVO_DIR_PIN);
  centralizar();

  Serial.println(F("ROB4M - teste de servos (T04)"));
  mostrarAjuda();
  imprimirAngulos();
}

void loop() {
  if (!Serial.available()) return;

  char comando = Serial.read();
  switch (comando) {
    case 'c': centralizar(); break;
    case 'q': moverEsquerdo(anguloEsq + PASSO_GRAUS); break;
    case 'a': moverEsquerdo(anguloEsq - PASSO_GRAUS); break;
    case 'w': moverDireito(anguloDir + PASSO_GRAUS); break;
    case 's': moverDireito(anguloDir - PASSO_GRAUS); break;
    case 'v': varrer(); break;
    case '?': mostrarAjuda(); return;
    default: return;  // ignora fim de linha e caracteres desconhecidos
  }
  imprimirAngulos();
}

void moverEsquerdo(int angulo) {
  anguloEsq = constrain(angulo, ANGULO_MIN, ANGULO_MAX);
  servoEsquerdo.write(anguloEsq);
}

void moverDireito(int angulo) {
  anguloDir = constrain(angulo, ANGULO_MIN, ANGULO_MAX);
  servoDireito.write(anguloDir);
}

void centralizar() {
  moverEsquerdo(ANGULO_CENTRO);
  moverDireito(ANGULO_CENTRO);
}

// Centro -> máximo -> mínimo -> centro, um grau por vez, nos dois servos.
void varrer() {
  Serial.println(F("Varredura em andamento..."));
  for (int a = ANGULO_CENTRO; a <= ANGULO_MAX; a++) {
    moverEsquerdo(a);
    moverDireito(a);
    delay(ATRASO_VARREDURA_MS);
  }
  for (int a = ANGULO_MAX; a >= ANGULO_MIN; a--) {
    moverEsquerdo(a);
    moverDireito(a);
    delay(ATRASO_VARREDURA_MS);
  }
  for (int a = ANGULO_MIN; a <= ANGULO_CENTRO; a++) {
    moverEsquerdo(a);
    moverDireito(a);
    delay(ATRASO_VARREDURA_MS);
  }
}

void imprimirAngulos() {
  Serial.print(F("SV1 (esq): "));
  Serial.print(anguloEsq);
  Serial.print(F(" | SV2 (dir): "));
  Serial.println(anguloDir);
}

void mostrarAjuda() {
  Serial.println(F("c = centralizar | q/a = SV1 +/- | w/s = SV2 +/- | v = varredura | ? = ajuda"));
  Serial.print(F("Limites: "));
  Serial.print(ANGULO_MIN);
  Serial.print(F(" a "));
  Serial.print(ANGULO_MAX);
  Serial.println(F(" graus"));
}

void desligarPonteH() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}
