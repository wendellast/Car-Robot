#include <SoftwareSerial.h>
#include "music.h"
#include "music_jojo.h"
#include <Servo.h>

SoftwareSerial mySerial(8, 7);  // RX | TX

int servoPin = 6;
int servoAngle = 0;


char command;  // Comando BLUE

//Servo Motor

Servo servo;
//Servo Motor

//Motores
int IN1 = 0;
int IN2 = 0;

int IN3 = 0;
int IN4 = 0;
//Motores

int xz = 0;  // Musica sorted

int led1_azul = 9;       // Led1 - Azul Alerta
int led1_vermelho = 13;  // Led1 - Azul Alerta

int buzzerPin = 10;  // Buzina

int buttonPin = 12;

int estadoButton = 0;
int vezes = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  servo.attach(servoPin);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(buttonPin, INPUT);
  naocabeca();
}



void loop() {

  estadoButton = digitalRead(buttonPin);




  if (estadoButton == 1) {  // Botão escolha de modo
    if (vezes > 2) {
      vezes = 0;
      vezes++;
      Serial.println(vezes);
      delay(500);

    } else {
       vezes++;
    Serial.println(vezes);
    delay(500);
    }

   
  }



  //MODO BLUE =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if (vezes == 1) {

    modBlue();
  }

  //MODO AUTO =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  else if (vezes == 2) {

    modAlto();
  }
}

void modAlto() {
  servo.write(40);
  delay(100);
  servo.write(140);
  
 
}

void modBlue() {
  digitalWrite(servoPin, LOW);

  if (mySerial.available()) {

    command = (mySerial.read());




    if (command == 'F') {
      led_azul();



    }

    else if (command == 'B') {
      led_vermelho();
    }


    else if (command == 'L') {
      esquerda();
    }

    else if (command == 'R') {
      direita();
    }

    else if (command == 'V') {
      buzina();
    }

    else if (command == 'v') {
      digitalWrite(buzzerPin, LOW);
    }

    else if (command == 'X') {
      digitalWrite(led1_azul, HIGH);
    }

    else if (command == 'x') {
      digitalWrite(led1_azul, LOW);
    }

    else {
      parado();
    }
  }
}





void led_vermelho() {
  pinMode(led1_vermelho, OUTPUT);
  pinMode(led1_azul, OUTPUT);

  digitalWrite(led1_vermelho, HIGH);
  digitalWrite(led1_azul, LOW);
}

void led_azul() {

  pinMode(led1_azul, OUTPUT);
  pinMode(led1_vermelho, OUTPUT);

  digitalWrite(led1_azul, HIGH);
  digitalWrite(led1_vermelho, LOW);
}

void frente() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void tras() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void parado() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void iniciar() {

  //Piscar LED AZUL


  digitalWrite(led1_azul, HIGH);
  delay(500);
  digitalWrite(led1_azul, LOW);
  delay(500);
  digitalWrite(led1_azul, HIGH);
  delay(500);
  digitalWrite(led1_azul, LOW);
  delay(500);
  digitalWrite(led1_azul, HIGH);
  delay(500);
  digitalWrite(led1_azul, LOW);
}

//FUNÇÃO PARA BALANCAR CABEÇA
void naocabeca() {


  servo.write(40);
  delay(250);
  servo.write(140);
  delay(250);
  servo.write(40);

  //servoCabeca.write(140);
  delay(250);
  servo.write(90);
}

void cabeca_reta() {
  servo.write(90);
  delay(100);
  servo.write(10);
  delay(100);
}

void beep(int speakerPin, float noteFrequency, long noteDuration) {
  int x;

  float microsecondsPerWave = 1000000 / noteFrequency;
  float millisecondsPerCycle = 1000 / (microsecondsPerWave * 2);
  float loopTime = noteDuration * millisecondsPerCycle;

  for (x = 0; x < loopTime; x++) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(microsecondsPerWave);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(microsecondsPerWave);
  }
}

void buzina() {

  xz = random(2, 4);  // Vai de 0 a 4

  if (xz == 2) {                    // Musica robot
    beep(buzzerPin, note_A7, 100);  //A
    beep(buzzerPin, note_G7, 100);  //G
    beep(buzzerPin, note_E7, 100);  //E
    beep(buzzerPin, note_C7, 100);  //C
    beep(buzzerPin, note_D7, 100);  //D
    beep(buzzerPin, note_B7, 100);  //B
    beep(buzzerPin, note_F7, 100);  //F
    beep(buzzerPin, note_C8, 100);  //C
    beep(buzzerPin, note_A7, 100);  //A
    beep(buzzerPin, note_G7, 100);  //G
    beep(buzzerPin, note_E7, 100);  //E
    beep(buzzerPin, note_C7, 100);  //C
    beep(buzzerPin, note_D7, 100);  //D
    beep(buzzerPin, note_B7, 100);  //B
    beep(buzzerPin, note_F7, 100);  //F
    beep(buzzerPin, note_C8, 100);  //C
  }

  else if (xz == 7) {  // Musica JOJO
    beep(buzzerPin, f5s, Qnote + Enote);
    beep(buzzerPin, d5, Hnote);
    beep(buzzerPin, d5, Snote);
    beep(buzzerPin, e5, Snote);
    beep(buzzerPin, f5, Enote + Snote);
    beep(buzzerPin, e5, Enote + Snote);
    beep(buzzerPin, d5, Enote);
    beep(buzzerPin, c5s, Enote + Snote);
    beep(buzzerPin, d5, Enote + Snote);
    beep(buzzerPin, e5, Enote);
    beep(buzzerPin, f5s, Qnote + Enote);
    beep(buzzerPin, b5, Qnote + Enote);
    beep(buzzerPin, b4, Enote);
    beep(buzzerPin, c5, Enote);
    beep(buzzerPin, d5, Enote + Snote);
    beep(buzzerPin, e5, Enote + Snote);
    beep(buzzerPin, d5, Enote);
    beep(buzzerPin, c5s, Enote + Snote);
    beep(buzzerPin, a5, Enote + Snote);
    beep(buzzerPin, g5, Enote);
    beep(buzzerPin, f6, Qnote + Enote);
    beep(buzzerPin, d6, Hnote);
    beep(buzzerPin, d6, Snote);
    beep(buzzerPin, e6, Snote);
    beep(buzzerPin, f6, Enote + Snote);
    beep(buzzerPin, e6, Enote + Snote);
    beep(buzzerPin, d6, Enote);
    beep(buzzerPin, c6, Enote + Snote);
    beep(buzzerPin, d6, Enote + Snote);
    beep(buzzerPin, e6, Enote);
    beep(buzzerPin, f6, Qnote + Enote);
    beep(buzzerPin, b6, Enote);
    beep(buzzerPin, c7s, Enote);
    beep(buzzerPin, d7, Enote + Snote);
    beep(buzzerPin, g6, Enote + Snote);
    beep(buzzerPin, f6s, Enote);
    beep(buzzerPin, f6, Snote + Enote);
    beep(buzzerPin, d7, Enote + Snote);
    beep(buzzerPin, a6s, Enote);
    beep(buzzerPin, b6, Qnote);
  }
}