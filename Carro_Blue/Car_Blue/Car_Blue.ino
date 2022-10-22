#include <SoftwareSerial.h>
#include <Ultrasonic.h>
#include <Servo.h>

#include "music.h"
#include "music_jojo.h"

#define Trig 2
#define Echo 3

//Config sensores >>> 
SoftwareSerial mySerial(8, 7);  // RX | TX

float distanciaObstaculo = 35;

Ultrasonic ultrasonico(Trig, Echo);

int servoPin = 6;
int servoAngle = 0;


char command;  // Comando BLUE

//Servo Motor

Servo servo;
//Servo Motor

//Motores Car Blue
int IN1 = 0;
int IN2 = 0;

int IN3 = 0;
int IN4 = 0;
//Motores Car Blue


//Motores Car Auto
#define  B1A 0
#define  B1B 0

#define  A1A 0
#define  A1B 0
//Motores Car Auto


//Variaveis
int led1_azul = 9;       // Led1 - Azul Alerta
int led1_vermelho = 13;  // Led1 - Azul Alerta

//Config Padrão
int buzzerPin = 10;  // Buzina
int buttonPin = 12;

int estadoButton = 0;
int vezes = 0;
int xz = 0;  // Musica sorted

int distanciaD;
int distanciaE;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  servo.attach(servoPin);

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  //Config Car BLUE
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //config Car Auto
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);



  //Carregando funções >>
  iniciar();
  naocabeca();
  cabeca_reta();
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
  Serial.println(ultrasonico.Ranging(CM));

  if (ultrasonico.Ranging(CM) <= distanciaObstaculo) {
    Andar(5);
    int statuss = Radar();
    delay(500);


    if (statuss == 1) {
      Andar(2);
      delay(600);
      Andar(4);
      delay(400);
      Andar(5);
    }
    if (statuss == 2) {
      Andar(2);
      delay(600);
      Andar(3);
      delay(400);
      Andar(5);
    }
    if (statuss == 0) {
      Andar(2);
      delay(500);
      Andar(4);
      delay(300);
      Andar(5);
    }
    delay(1000);
  } else {
    Andar(1);
  }
}

void modBlue() {
  digitalWrite(servoPin, LOW);
  servo.attach(0);

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



//Car Auto =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void Andar(int direcao) {
  if (direcao == 1) {  // anda pra frente
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);

    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }

  if (direcao == 2) {  // anda pra trás
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
  }

  if (direcao == 3) {  // faz curva pra direita
    digitalWrite(B1A, HIGH);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, HIGH);
  }

  if (direcao == 4) {  // faz curva pra esquerda
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, HIGH);
    digitalWrite(A1A, HIGH);
    digitalWrite(A1B, LOW);
  }

  if (direcao == 5) {  // FREIA
    digitalWrite(B1A, LOW);
    digitalWrite(B1B, LOW);
    digitalWrite(A1A, LOW);
    digitalWrite(A1B, LOW);
    buzina();
  }
}

int Radar() {
  delay(1000);
  servo.write(175);
  delay(1000);
  distanciaD = ultrasonico.Ranging(CM);

  delay(1000);
  servo.write(10);
  delay(1000);
  distanciaE = ultrasonico.Ranging(CM);

  delay(1000);
  servo.write(90);

  if (distanciaD > distanciaE) {
    return 1;  // se tiver espaço na direita
  }
  if (distanciaD < distanciaE) {
    return 2;  //se tiver espaço na esquerda
  }
  if (distanciaD == distanciaE) {
    return 0;
  }
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