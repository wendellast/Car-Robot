#include <SoftwareSerial.h>
#include "music.h"
#include "music_jojo.h"

SoftwareSerial bluetooth(8, 7);

char comando;

int IN1 = 4;
int IN2 = 5;

int IN3 = 6;
int IN4 = 1;

int xz = 0;

int led1 = 9;  // Led1 -

int buzzerPin = 10;  // Buzina
int speakPin = 10; // Buzina




void setup() {
  //Define os pinos como saida

  bluetooth.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(led1, LOW);
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
      digitalWrite(led1, HIGH);
    }

    else if (comando == 'x') {
      digitalWrite(led1, LOW);
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

    xz = random(1, 5); // Vai de 0 a 4
    
    if (xz == 2)    { // Musica robot
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

    else if (xz == 3){ // Musica JOJO
    beep(buzzerPin, f5s, Qnote+Enote);
    beep(buzzerPin,  d5, Hnote);
    beep(buzzerPin,  d5, Snote);
    beep(buzzerPin,  e5, Snote);
    beep(buzzerPin,  f5, Enote+Snote);
    beep(buzzerPin,  e5, Enote+Snote);
    beep(buzzerPin,  d5, Enote);
    beep(buzzerPin,  c5s, Enote+Snote);
    beep(buzzerPin,  d5, Enote+Snote);
    beep(buzzerPin,  e5, Enote);
    beep(buzzerPin, f5s, Qnote+Enote);
    beep(buzzerPin, b5, Qnote+Enote);
    beep(buzzerPin, b4, Enote);
    beep(buzzerPin, c5, Enote);
    beep(buzzerPin,  d5, Enote+Snote);
    beep(buzzerPin,  e5, Enote+Snote);
    beep(buzzerPin,  d5, Enote);
    beep(buzzerPin,  c5s, Enote+Snote);
    beep(buzzerPin,  a5, Enote+Snote);
    beep(buzzerPin,  g5, Enote);
    beep(buzzerPin,  f6, Qnote+Enote);
    beep(buzzerPin,  d6, Hnote);
    beep(buzzerPin,  d6, Snote);
    beep(buzzerPin,  e6, Snote);
    beep(buzzerPin,  f6, Enote+Snote);
    beep(buzzerPin,  e6, Enote+Snote);
    beep(buzzerPin,  d6, Enote;
    beep(buzzerPin,  c6, Enote+Snote);
    beep(buzzerPin,  d6, Enote+Snote);
    beep(buzzerPin,  e6, Enote);
   beep(buzzerPin,  f6, Qnote+Enote);
     beep(buzzerPin,  b6, Qnote+Enote);

  
    tone(speakPin, b6);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, c7s);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d7);
    delay(Enote+Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, g6);
    delay(Enote+Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, f6s);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, f6);
    delay(Snote+Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d7);
    delay(Enote+Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, a6s);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, b6);
    delay(Qnote);
    noTone(speakPin);
    delay(25);      
    }





}

 