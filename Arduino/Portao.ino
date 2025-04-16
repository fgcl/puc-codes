#include <Stepper.h>

int voltas = 500;
int bi = 3; // Botão iniciar
int bp = 2; // Botão parar
int bv = 4; // Botão voltar
int vd = 5; // LED verde
int am = 6; // LED amarelo
int vm = 7; // LED vermelho

Stepper motor(voltas, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(40);
  pinMode(vd, OUTPUT);
  pinMode(am, OUTPUT);
  pinMode(vm, OUTPUT);
  pinMode(bi, INPUT);
  pinMode(bp, INPUT);
  pinMode(bv, INPUT);
  attachInterrupt(digitalPinToInterrupt(bp), pararPortao, FALLING);
  Serial.begin(9600);
}

void pararPortao() {
  digitalWrite(am, HIGH);
  motor.step(0);
  Serial.println("Parado");
}

void loop() {
  if (digitalRead(bi) == HIGH) {
    digitalWrite(vd, HIGH);
    digitalWrite(am, LOW);
    digitalWrite(vm, LOW);
    motor.step(2048);
    digitalWrite(vd, LOW);
  }
  
  if (digitalRead(bv) == HIGH) {
    digitalWrite(vd, LOW);
    digitalWrite(am, LOW);
    digitalWrite(vm, HIGH);
    motor.step(-2048);
    digitalWrite(vm, LOW);
  }

  Serial.println("Loop ativo");
  
  digitalWrite(am, LOW);
  delay(100);
}
