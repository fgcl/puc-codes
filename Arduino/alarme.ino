#include "SoftwareSerial.h"
SoftwareSerial ESP_Serial(5, 6);
String ssid = "projeto";
String psswd = "felipe123"; // senha
String response = "";

/* Declaração de Variáveis Globais */
const int botoes = A0,
      sensortemp = A5,
          pedal = 2,
          ledvrm = 8,
          ledama = 9,
          ledvrd = 10,
          som = 12;

int   led = 0,
    valor = 0,
    ctvrm = 0,
    ctvrd = 0,
    ctama = 0,
     frio = 0,
   quente = 0;
float calculo, temperatura;

void setup() {
  /* Incialização dos seriais */
  ESP_Serial.begin(9600);
  Serial.begin(9600);

  delay(1000);

  /* Configurando o ESP8266 */
  Serial.println("Conectando ao ESP8266...");
  sendCommand("AT");
  readResponse(1000);

  Serial.println("Mudando o modo AP CWMODE=2...");
  sendCommand("AT+CWMODE=2");
  readResponse(1000);

  Serial.println("Criando a rede com CWSAP...");
  String CWSAP = "AT+CWSAP=\"" + ssid + "\",\"" + psswd + "\",1,3"; // Canal 1, WPA_PSK
  sendCommand(CWSAP);
  readResponse(5000);

  Serial.println("Testando a rede...");
  sendCommand("AT+CWSAP?");
  readResponse(1000);

  Serial.println("Verificando (1/2)...");
  sendCommand("AT+CIFSR");
  readResponse(1000);

  Serial.println("Configurando (2/2)...");
  sendCommand("AT+CIPMUX=1");
  readResponse(1000);

  Serial.println("Ativando o servidor...");
  sendCommand("AT+CIPSERVER=1,80");
  readResponse(1000);

  /* Definição de entradas/saidas digitais */
  pinMode(ledvrm, OUTPUT);
  pinMode(ledama, OUTPUT);
  pinMode(ledvrd, OUTPUT);
  pinMode(som, OUTPUT);
  pinMode(pedal, INPUT);
}

int ativo = 1;
void loop() {
  /* DEBUG */
  //Serial.println(millis());
  //Serial.println(temperatura);
  //Serial.println(valor);
  //Serial.println(digitalRead(pedal));

  if (millis() >= 15000 && ativo) {
    Serial.println("ALARME!!! Acorde!");
    while(digitalRead(pedal) == 0){
      tone(som, 800, 500);
      delay(500);
      ligarled(ledvrm);
    }
    tone(som, 600, 500);
    ativo = 0;
  }
  /* Leitura de Temperatura. */
  calculo = (analogRead(sensortemp) * 5.0) / 1023.0;
  temperatura = calculo / 0.01;
  if(digitalRead(pedal)){
    if (24.00 - temperatura >= 1){
      frio = temperatura;
    }else{
      quente = temperatura;
    }
  }
  /* Leitura dos botões. */
  valor = analogRead(botoes);
  if(valor > 100 && valor < 150){
    Serial.println("Botao esquerdo pressionado (raiva)");
    ctvrm++;
    ligarled(ledvrm);
  }
  else if(valor > 50 && valor < 100){
    Serial.println("Botao do meio pressionado (tedio)");
    ctama++;
    ligarled(ledama);
  }
  else if(valor>150){
    Serial.println("Botao direito pressionado (feliz)");
    ctvrd++;
    ligarled(ledvrd);
  }
  delay(150);

  // esp 
  if (Serial.available()){
    ESP_Serial.write(Serial.read());
  }
  if (ESP_Serial.available()) {
    if (ESP_Serial.find("+IPD,")) {
      delay(500);
      char id = ESP_Serial.peek(); //pega ID da conexao

      /* Página HTML */
      String webpage = String("HTTP/1.1 200 OK\r\n") +
                       "Content-Type: text/html\r\n" +
                       "Connection: close\r\n" +
                       "\r\n" +
                       "<p>Raiva: <b>" + ctvrm + "</b> vezes</p>" +
                       "<p>Cansado: <b>" + ctama + "</b> vezes</p>" +
                       "<p>Feliz: <b>" + ctvrd + "</b> vezes</p>" +
                       "<p>Temperatura minima: " + frio + "</p>" +
                       "<p>Temperatura maxima: " + quente + "</p>";

      String cipSend = "AT+CIPSEND=";
      cipSend += (int(id) - 48);
      cipSend += ",";
      cipSend += webpage.length();
      Serial.println(webpage.length());
      sendCommand(cipSend);
      readResponse(500);

      sendCommand(webpage);
      readResponse(750);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += (int(id) - 48);
      sendCommand(closeCommand);
      readResponse(750);
    }
  }
}

void ligarled(int led){
  Serial.println(led);
  digitalWrite(ledvrd, LOW);
  digitalWrite(ledama, LOW);
  digitalWrite(ledvrm, LOW);
  delay(100);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

// esp
void sendCommand(String cmd) {
  ESP_Serial.println(cmd);
}

void readResponse(unsigned int timeout) {
  unsigned long timeIn = millis();
  response = "";
  while (timeIn + timeout > millis()) {
    if (ESP_Serial.available()) {
      char c = ESP_Serial.read();
      response += c;
    }
  }
  Serial.println(response);
}