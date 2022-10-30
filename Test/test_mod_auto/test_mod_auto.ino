#include <NewPing.h>                // SE DEFINE AL SENSOR ULTRASONICO 
#include <Servo.h>                  // SE DEFINE AL SERVOMOTOR. 

#define TRIG_PIN 12                 // SE DEFINE EL SENSOR ULTRASONICO, TRIG VA AL PIN A0 DEL ARDUINO UNO.
#define ECHO_PIN 4                 // SE DEFINE EL SENSOR ULTRASONICO, ECHO VA AL PIN A1 ARDUINO UNO.
#define MAX_DISTANCE 200            
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

boolean goesForward=false;         
int distance = 100;               
int speedSet = 0;               
                                  
const int motorPin1  = 5;          //MOTOR 1 IZQUIERDA
const int motorPin2  = 6;          
const int motorPin3  = 3;          //MOTOR 2 DERECHA
const int motorPin4  = 11;  

void setup() {

  myservo.attach(8);              // PIN PWM DEL SERVO VA AL PIN 3 DEL ARDUINO UNO.
  myservo.write(115);              // VELOCIDAD DEL SERVO.
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance<=15)                //SE ACTIVA EL SENSOR ULTRASONICO CUANDO DETECTA OBSTACULOS A MENOS DE 15CM.
 {
  moveStop();                   
  delay(200);                   
  moveBackward();              //EL CARRITO SE DETIENE Y SE VA HACIA ATRAS POR 800 MILISEGUNDOS.
  delay(800);                      
  
  moveStop();
  delay(200);
  distanceR = lookRight();       
  delay(200);
  distanceL = lookLeft();         
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();           
    moveStop();
  }
  
      else
      
  {
    turnLeft();            
    moveStop();
  }
  
 }else   
                        
 {
  moveForward();         
 }
 distance = readPing();
}

int lookRight()          
{
    myservo.write(50);    
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);        
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  } 
  
void moveForward() {        //CARRITO AVANZA


    analogWrite(motorPin1, 180);       
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 180);     
    analogWrite(motorPin4, 0);  
  
}

void moveBackward() {        //HACIA ATRAS
    
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);       
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);      
  
}  

void turnRight() {     //GIRA A LA DERECHA Y AVANZA
  
    analogWrite(motorPin1, 180);     
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);   
    delay(300);
    moveForward();      
  
} 
 
void turnLeft() {           //GIRA A LA IZQUIERDA Y AVANZA
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);   
    analogWrite(motorPin3, 180);    
    analogWrite(motorPin4, 0);     
    delay(300);
    moveForward();
}  
