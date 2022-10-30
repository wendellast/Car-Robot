#include <Ultrasonic.h>
#include <Servo.h>

#include "music.h"
#include "music_jojo.h"

#define pinoServo 8
#define Trig 12
#define Echo 4

int tempo = 100;  //variável usada para definir o tempo de acionamento do buzzer
int frequencia = 0;
unsigned long millisTarefa1 = millis();  //variável que recebe o tempo atual em milissegundos
int temp = 250;

int xz = 0;         // Sorteia musica
int buzzerPin = 7;  // Buzina

int distanciaD;
int distanciaE;


// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;  // Define velocidade padrão 0 &lt; x &lt; 255.
char state;



//LEd
int led1_azul = 13;



float distanciaObstaculo = 25;

Ultrasonic ultrasonico(Trig, Echo);

Servo servo;


const int A1A = 5;
const int A1B = 6;
const int B1A = 3;
const int B1B = 11;

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
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(led1_azul, OUTPUT);


  //Radar();
  iniciar();
  naocabeca();
  cabeca_reta();
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
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }

  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 100);
    analogWrite(motorB2, 0);
  }

  else if (state == 'I') {  // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    analogWrite(motorA1, 100);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }

  else if (state == 'B') {  // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }

  else if (state == 'J') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
  }

  else if (state == 'H') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }

  else if (state == 'R') {  // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  } else if (state == 'L') {  // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);

  } else if (state == 'S') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }

  else if (state == 'X') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    modAlto();
  }

  else if (state == 'V') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    buzina();
  }

  else if (state == 'v') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(buzzerPin, LOW);

  } else if (state == 'W') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led1_azul, HIGH);
    
  } else if (state == 'w') {  // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(led1_azul, LOW);
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


void Andar(int direcao) {

  direcao = 1;
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
void leds() {
  if (millis() - millisTarefa1 > temp) {  //Se o resultado da subtração de millis() - millisTarefa1 for maior que temp (250 milissegundo)
    digitalWrite(led1_azul, HIGH);        //Liga o LED azul
                                          //Desliga o LED vermelho
  } else {                                //Senão
    digitalWrite(led1_azul, LOW);         //Desliga o azul
                                          //Liga o LED vermelho
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

void buzina() {

  xz = random(1, 4);  // Vai de 0 a 4

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

  else if (xz == 1) {                                             // Sireni
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