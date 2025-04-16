/* Partida direta com led.
Descriçao: Ao apertar o botão uma vez, irá ligar o led. Na segunda vez, irá desligar o led.
Versao: 1.0
Author: Felipe Gonçalves
*/

// definiçao de variaveis globais.
int L = 2; // pino 2 definido como a variavel L.
int btn = 10; // pino 10 definido como a variavel btn.
int var = LOW; // definir desligado para variavel var.
int vezes; // variavel para armazenar quantas vezes o botao foi apertado.

// funçao de inicializaçao.
void setup() {
  // definir os pins usados.
  pinMode(L, OUTPUT); // o pino 2 será uma saida.
  pinMode(btn, INPUT); // o pino 10 será uma entrada.
  Serial.begin(9600); // baundrate da comunicaçao entre arduino e terminal
  vezes = 0; // definir a variavel vezes (vezes que o led foi pressionado) inicialmente como 0.
}

// funçao de loop
void loop() {
  var = digitalRead(btn); // ler os valores do pino 10.
  Serial.println(var); // mostrar se o pino 10 está recebendo energia ou não.
  if (var == HIGH){ //verificaçao se o botão foi pressionado.
    vezes += 1; // aumenta o valor da variavel gradualmente.
    digitalWrite(L, HIGH); //liga o led
  }
  if (vezes>=2){ // verificar se a variavel vezes é maior ou igual a 2.
    digitalWrite(L, LOW); // apaga o led.
    vezes = 0; // define a variavel vezes para 0.
  }
  delay(100); // espere 100ms para continuar o loop.
}