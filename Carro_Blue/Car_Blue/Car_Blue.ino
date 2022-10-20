
#include <SoftwareSerial.h>
#include "music.h"
#include "music_jojo.h"

SoftwareSerial bluetooth(8, 7);
 
char comando; 

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 1;



int led1 = 9; // Led1 -

int buzzerPin = 10; // Buzina


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
      tras(); }

      
    else if (comando == 'L') {
      esquerda();} 
      
    else if (comando == 'R') {
      direita(); }
       
    else if (comando == 'V') {
      buzina();
      }
    
    else if (comando == 'v') {
      digitalWrite(buzzerPin, LOW);
      }
 
    else {
      parado();}
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
  digitalWrite(IN4,LOW);
}

void beep (int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  
  float microsecondsPerWave = 1000000/noteFrequency;
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  float loopTime = noteDuration * millisecondsPerCycle;
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     

void buzina(){
         
          beep(buzzerPin, note_A7,100); //A 
          beep(buzzerPin, note_G7,100); //G 
          beep(buzzerPin, note_E7,100); //E 
          beep(buzzerPin, note_C7,100); //C
          beep(buzzerPin, note_D7,100); //D 
          beep(buzzerPin, note_B7,100); //B 
          beep(buzzerPin, note_F7,100); //F 
          beep(buzzerPin, note_C8,100); //C 
          beep(buzzerPin, note_A7,100); //A 
          beep(buzzerPin, note_G7,100); //G 
          beep(buzzerPin, note_E7,100); //E 
          beep(buzzerPin, note_C7,100); //C
          beep(buzzerPin, note_D7,100); //D 
          beep(buzzerPin, note_B7,100); //B 
          beep(buzzerPin, note_F7,100); //F 
          beep(buzzerPin, note_C8,100); //C 
          
              
}  

          
