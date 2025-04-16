/* Projeto Arduino som de microondas
*/

int sirene = 2; // definir o pino da sirene.
int etapa = 0; // etapa incial do microondas.
int totaletapas = 30; // etapa até ficar pronto.
int tempo = 300; // tempo dos delays.

void setup() {
  pinMode(sirene, OUTPUT);
}

void loop() {
  etapa += 1;
  // verificar se o tempo já acabou.
  if (etapa >= totaletapas) {
    tone(sirene, 200, 1000); // som final.
    delay(2000);
    etapa = 0; // redefinir a etapa.
  }
  // verifica qual a etapa do microondas e define um tempo para o barulho cada vez menor.
  if (etapa < 5) {
    tempo = 600;
  } else if (etapa < 15) {
    tempo = 500;
  } else if (etapa < 25) {
   tempo = 400;
  }
  delay(tempo); // aguarda um tempo para inciar.
  tone(sirene, 2000, tempo); // barulho de microondas.
  delay(tempo); // adiciona um delay até que o barulho termine.
}