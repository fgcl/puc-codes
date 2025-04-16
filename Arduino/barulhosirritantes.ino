/* Projeto Arduino Musical
Descriçao:
Versao:
*/

//definiçao de variaveis globais
int mus = 7;
int doh = 262;
int mi = 330;
int sol = 392;
int si = 494;
int var;
int poten = A5;
int tempo = 200;

//funçao de inicializaçao
void setup() {
  // definir os pins usados.
  pinMode(mus, OUTPUT);
  pinMode(poten, INPUT);
  Serial.begin(57600);
}

// funçao de loop
void loop() {
  var = AnalogRead(poten);
  Serial.println(var);
  if (var < 250){
    tone(mus, doh, tempo);
  }
  else if (var>=250&&var<500){
    tone(mus, mi, tempo);
  }
  else if (var>=500&&var<750){
    tone(mus, sol, tempo);
  }
  else if (var>=750){
    tone(mus, si, tempo);
  }
  delay(tempo);
}