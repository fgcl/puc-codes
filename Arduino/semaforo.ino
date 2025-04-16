/*
Projeto semaforo 1.0
*/

//definiçao de variaveis constantes
const int vermelho = 1;
const int amarelo = 2;
const int verde = 3;

//funçao de inicializaçao
void setup() {
  // definir os pins usados.
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  Serial.begin(57600);
}

// funçao de loop
void loop() {
  char comando = Serial.read();
  Serial.println(comando);
  if (comando == "ligar"){
  //ligar o verde pin3 por 5s
    digitalWrite(verde, HIGH); //liga o led
    delay(5000); //delay de 5s
    digitalWrite(verde, LOW); //desliga o led verde
    digitalWrite(amarelo, HIGH);
    delay(1000); //delay do amarelo
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, HIGH);
    delay(4000); //delay do vermelho
    digitalWrite(vermelho, LOW);
  }
}
