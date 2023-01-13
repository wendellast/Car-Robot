#include <Servo.h>
#include <HCSR04.h>

#include "music.h"
#include "music_jojo.h"
#include "music_mortal_kobat.h"
//Versão --> 2.0
#define pinoServo 8
#define Trig 12
#define Echo 4
#define minDist 15

HCSR04 sensorDistancia(Trig, Echo);
int tempo = 100;  //variável usada para definir o tempo de acionamento do buzzer
int frequencia = 0;
unsigned long millisTarefa1 = millis();  //variável que recebe o tempo atual em milissegundos
int temp = 250;

int xz = 0;         // Sorteia musica
int buzzerPin = 7;  // Buzina
int speakPin = 7;   // Buzina

int distanciaD;
int distanciaE;

unsigned long tempoLeitura = 0;  // VARIAVEL PARA CONTROLAR TEMPO DE LEITURA DO HCSR04
float distObstaculo = 30;        // VARIÁVEL PARA ARMAZENAR DISTANCIA DOS OBSTÁCULOS
bool terraFirme;                 // VÁRIÁVEL PARA CHECAR SE HÁ CHÃO A FRENTE DO ROBO
bool perigo = false;

// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;  // Define velocidade padrão 0 &lt; x &lt; 255.
char state;



//LEd
int led1_azul = 13;
int led2_vermelho = 10;
const int ledPin2 = 13;
const int ledPin1 = 0;
int counter = 0;



Servo servo;



// Define os pinos de utilização do Driver L298.
const int motorA1 = 5;   // Pin  5 of L293.
const int motorA2 = 6;   // Pin  6 of L293.
const int motorB1 = 3;   // Pin 10 of L293.
const int motorB2 = 11;  // Pin 9 of L293.



void setup() {
  Serial.begin(9600);

  servo.attach(pinoServo);

  // Inicializa as portas como entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);


  //pinos da ponte H
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1_azul, OUTPUT);
  pinMode(led2_vermelho, OUTPUT);



  iniciar();
  naocabeca();
  delay(1000);
  checarPerigo();

  // Inicializa a comunicação serial em 9600 bits.
}

void loop() {

  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }

  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    vSpeed = 0;
  } else if (state == '4') {
    vSpeed = 100;
  } else if (state == '6') {
    vSpeed = 155;
  } else if (state == '7') {
    vSpeed = 180;
  } else if (state == '8') {
    vSpeed = 200;
  } else if (state == '9') {
    vSpeed = 230;
  } else if (state == 'q') {
    vSpeed = 255;
  }


  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    //servo.write(90);
    checarPerigo();
    if (perigo == false) {
      analogWrite(motorB1, vSpeed);
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB2, 0);
    } else {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }
  }

  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    //servo.write(140);
    checarPerigo();
    if (perigo == false) {
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 100);
      analogWrite(motorB2, 0);
    } else {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }
  }

  else if (state == 'I') {  // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    //servo.write(40);
    checarPerigo();
    if (perigo == false) {
      analogWrite(motorA1, 100);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorB2, 0);
    } else {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }
  }

  else if (state == 'B') {  // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    //servo.write(90);
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }

  else if (state == 'J') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    //servo.write(90);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
  }

  else if (state == 'H') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    //servo.write(90);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }

  else if (state == 'R') {  // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    //servo.write(30);
    checarPerigo();
    if (perigo == false) {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, vSpeed);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorB2, 0);
    } else {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }

  } else if (state == 'L') {  // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    //servo.write(150);
    checarPerigo();
    if (perigo == false) {
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, vSpeed);
    } else {
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }

  } else if (state == 'S') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    //servo.write(90);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }

  else if (state == 'V') {
    buzina();
  }

  else if (state == 'v') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(buzzerPin, LOW);
    digitalWrite(speakPin, LOW);

  } else if (state == 'W') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led1_azul, HIGH);

  }

  else if (state == 'w') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led1_azul, LOW);
  } else if (state == 'U') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led2_vermelho, HIGH);

  }

  else if (state == 'u') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led2_vermelho, LOW);
  }
  else if (state == 'X'){
    naocabeca();
    
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


//FUNÇÃO PARA CHECAR PERIGO
void checarPerigo() {
  if ((millis() - tempoLeitura) > 500) {     // LER DISTANCIA A CADA 500 MILISEGUNDOS
    distObstaculo = sensorDistancia.dist();  // LEITURA DA DISTÂNCIA EM CM DO OBSTÁCULO À FRENTE
    tempoLeitura = millis();                 // ATRIBUI O VALOR ATUAL DE MILLIS À VARIÁVEL DE CONTROLE
    Serial.println(distObstaculo);
  }



  if ((distObstaculo < minDist)) {  // PARA O ROBO CASO NÃO TENHA CHÃO OU ENCONTRE UM OBSTÁCULO PERTO
    if (!perigo) {
      perigo = true;  // GUARDA VALOR PARADO PARA LEMBRAR QUE TEM OBSTÁCULO À FRENTE DURANTE A PRÓXIMA EXECUÇÃO DO LOOP
      buzi_alert();
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
    }
  } else {
    perigo = false;
  }
}




//FUNÇÃO PARA BALANCAR CABEÇA
void naocabeca() {
  servo.write(40);
  delay(250);
  servo.write(140);
  delay(250);
  servo.write(40);
  delay(250);
  servo.write(140);
  delay(250);
  servo.write(90);
}


void leds() {
  if (millis() - millisTarefa1 > temp) {  //Se o resultado da subtração de millis() - millisTarefa1 for maior que temp (250 milissegundo)
    digitalWrite(led1_azul, HIGH);        //Liga o LED azul
    digitalWrite(led2_vermelho, LOW);     //Desliga o LED vermelho
  } else {                                //Senão
    digitalWrite(led1_azul, LOW);         //Desliga o azul
    digitalWrite(led2_vermelho, HIGH); 
    digitalWrite(led2_vermelho, LOW);    //Liga o LED vermelho
  }
  if ((millis() - millisTarefa1) > (2 * temp)) {  //Se o resultado da subtração de millis() - millisTarefa1 for maior que 2 vezes temp (500 milissegundo)
    millisTarefa1 = millis();                     //Atribui a millisTarefa1 o valor de millis()
  }
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

void buzi_alert() {
  digitalWrite(led2_vermelho, HIGH); 
  delay(100);
  digitalWrite(led2_vermelho, LOW); 
  
  
   
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

void buzina() {

  xz = random(1, 5);  // Vai de 0 a 4
  Serial.println(xz);

  if (xz == 1) {                    // Musica robot
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

  else if (xz == 2) {                                             // Sireni
    for (frequencia = 150; frequencia < 1800; frequencia += 1) {  //Define frequencia igual a 150; verifica se frequencia é menor que 1800; realiza a soma frequencia = frequencia + 1
      leds();                                                     //Chama a função led
      tone(buzzerPin, frequencia, tempo);                         //Aciona o led com frequência definida pelo for e tempo igual a 100 milissegundos
      delay(1);                                                   //delay de 1 milissegundos
    }
    for (frequencia = 1800; frequencia > 150; frequencia -= 1) {  //Define frequencia igual a 1800; verifica se frequencia é maior que 150; realiza a subtração frequencia = frequencia - 1
      leds();                                                     //Chama a função led
      tone(buzzerPin, frequencia, tempo);                         //Aciona o led com frequência definida pelo for e tempo igual a 100 milissegundos
      delay(1);                                                   //delay de 1 milissegundos
    }
  }


  else if (xz == 3) {  // Musica JOJO
    tone(speakPin, f5s);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, d5);
    delay(Hnote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, d5);
    delay(Snote);
    noTone(speakPin);
    delay(12.5);

    tone(speakPin, e5);
    delay(Snote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, f5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, e5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d5);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, c5s);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, e5);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, f5s);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, b5);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, b4);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, c5s);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, d5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, e5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d5);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, c5s);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, a5);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, g5);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, f6s);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, d6);
    delay(Hnote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, d6);
    delay(Snote);
    noTone(speakPin);
    delay(12.5);

    tone(speakPin, e6);
    delay(Snote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, f6);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, e6);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d6);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, c6s);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d6);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, e6);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, f6s);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, b6);
    delay(Qnote + Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, b6);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, c7s);
    delay(Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d7);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, g6);
    delay(Enote + Snote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, f6s);
    delay(Enote);
    noTone(speakPin);
    delay(50);

    tone(speakPin, f6);
    delay(Snote + Enote);
    noTone(speakPin);
    delay(25);

    tone(speakPin, d7);
    delay(Enote + Snote);
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

  else if (xz == 4) {  // Music Mortal kobat
    firstSection();
    firstSection();
    secondSection();
    thirdSection();
    thirdSection();
  }
}

void beep(int note, int duration) {
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);


  //Play different LED depending on value of 'counter'
  if (counter % 2 == 0) {
    digitalWrite(led1_azul, HIGH);
    delay(duration);
    digitalWrite(led1_azul, LOW);
  } else {
    digitalWrite(led2_vermelho, HIGH);
    delay(duration);
    digitalWrite(led2_vermelho, LOW);
  }

  //Stop tone on buzzerPin
  noTone(buzzerPin);

  delay(50);

  //Increment counter
  counter++;
}

void firstSection() {
  beep(AA3, 200);
  beep(AA3, 200);
  beep(C4, 200);
  beep(AA3, 200);
  beep(D4, 200);
  beep(AA3, 200);
  beep(E4, 200);
  beep(D4, 200);
  beep(C4, 200);
  beep(C4, 200);
  beep(E4, 200);
  beep(C4, 200);
  beep(G4, 200);
  beep(C4, 200);
  beep(E4, 200);
  beep(C4, 200);
  beep(G3, 200);
  beep(G3, 200);
  beep(B3, 200);
  beep(G3, 200);
  beep(C4, 200);
  beep(G3, 200);
  beep(D4, 200);
  beep(C4, 200);
  beep(F3, 200);
  beep(F3, 200);
  beep(AA3, 200);
  beep(F3, 200);
  beep(C4, 200);
  beep(F3, 200);
  beep(C4, 200);
  beep(B3, 200);
}
void secondSection() {
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(G3, 200);
  beep(C4, 200);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(G3, 200);
  beep(E3, 200);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(G3, 200);
  beep(C4, 200);
  beep(AA3, 325);
  beep(AA3, 325);
  beep(AA3, 200);
  beep(AA3, 75);
  beep(AA3, 325);
  beep(AA3, 450);
}

void thirdSection() {
  beep(AA3, 75);
  beep(E4, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 75);
  beep(G3, 200);
  beep(AA3, 75);
  beep(E4, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 75);
  beep(G3, 200);
  beep(AA3, 75);
  beep(E4, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(AA3, 75);
  beep(Bb3, 75);
  beep(G3, 200);
  beep(AA3, 75);
  beep(E4, 200);
  beep(AA3, 75);
  beep(C4, 200);
  beep(G3, 75);
  beep(G3, 200);
  beep(G3, 75);
  beep(AA3, 200);
  beep(AA3, 450);
}
