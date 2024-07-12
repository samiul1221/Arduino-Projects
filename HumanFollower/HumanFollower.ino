#include "NewPing.h"
#include<Servo.h>

#define TrigPin 2
#define EchoPin 3
void stop();
void right();
void left();
void forward();
void backward();
Servo myservo;
NewPing sonar(TrigPin,EchoPin,400);
int distance;
int LF = 12;
int LB = 11;
int RB = 10;
int RF = 9;
int RS = 7;
int LS = 6;
void setup() {

Serial.begin(9600);
myservo.attach(5);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print("Distance : ");
  distance = sonar.ping_cm();
  // Serial.print(distance);
  int LSV = digitalRead(LS);
  int RSV = digitalRead(RS);
  if (distance <=15 && (LSV ==1 && RSV ==1)) {
    backward();
  }
  else if ((LSV ==0) && (RSV == 1) ){
    left();
  }
  else if ((LSV ==1) && (RSV ==0)){
    right();
  }
  else if(distance >15){
    stop();
  }


  
}

void forward(){
  digitalWrite(RF,HIGH);
  digitalWrite(LF,HIGH);
  digitalWrite(RB,LOW);
  digitalWrite(LB,LOW);

}

void right(){
  digitalWrite(RF,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,HIGH);

}

void left(){
  digitalWrite(RF,LOW);
  digitalWrite(LF,HIGH);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,LOW);

}

void backward(){
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,HIGH);

}

void stop(){
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,LOW);

}

