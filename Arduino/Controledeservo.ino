/* Projeto Arduino
*/
#include <Servo.h>
int pot = A3;
int var;
int deg = 0;
Servo felipe;
void setup(){

  Serial.begin(9600);
  pinMode(pot, INPUT);
  felipe.atach(6);
}

void loop(){
  var = analogRead(pot);
  Serial.println(var);
  if(var>=500)
    deg = 180;
  else
    deg= 90;
  felipe.write(deg);
  delay(100);
}