#include <SoftwareSerial.h>
#include "music.h"
#include "music_jojo.h"
#include <Servo.h>

SoftwareSerial bluetooth(8, 7);

char comando; // Comando BLUE

//Servo Motor
#define pinServo1 11
Servo servoCabeca;
//Servo Motor

//Motores
int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 1;
//Motores

int xz = 0;  // Musica sorted

int led1_azul = 9;  // Led1 - Azul Alerta

int buzzerPin = 10;  // Buzina



void setup() {
  //Define os pinos como saida

  bluetooth.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(led1_azul, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  servoCabeca.attach(pinServo1);  
  
  iniciar();
  cabeca_reta();
  naoCabeca();
  cabeca_reta();
}



void loop() {

  while (bluetooth.available()) {

    comando = bluetooth.read();

    if (comando == 'F') {
      frente();
    }

    else if (comando == 'B') {
      tras();
    }


    else if (comando == 'L') {
      esquerda();
    }

    else if (comando == 'R') {
      direita();
    }

    else if (comando == 'V') {
      buzina();
    }

    else if (comando == 'v') {
      digitalWrite(buzzerPin, LOW);
    }

    else if (comando == 'X') {
      digitalWrite(led1_azul, HIGH);
    }

    else if (comando == 'x') {
      digitalWrite(led1_azul, LOW);
    }

    else {
      parado();
    }
  }
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
void naoCabeca(){
  

  servoCabeca.write(40);
  delay(250);  
  servoCabeca.write(140);
  delay(250); 
  servoCabeca.write(40);
  delay(250);
  //servoCabeca.write(140);
  //delay(250);
  servoCabeca.write(90);
  delay(250);
}

void cabeca_reta(){
  servoCabeca.write(90);
  delay(100);
  servoCabeca.write(10);
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

  else if (xz == 3) {  // Musica JOJO
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