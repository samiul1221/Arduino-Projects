#include "NewPing.h"
#include<Servo.h>

#define TP 9
#define EP 8
int val;
void Forward();
void Turn_Right();
void Turn_Left();
void STOP();
int Left_Forward = 3;
int Left_Backward = 2;

int Right_Forward = 4;
int Right_Backward = 5;

Servo ms;
String command;


NewPing sonar(TP,EP,400);
float distance;
void setup() {
pinMode(Left_Backward,OUTPUT);
pinMode(Left_Forward,OUTPUT);
pinMode(Right_Forward,OUTPUT);
pinMode(Right_Backward,OUTPUT);
pinMode(8,OUTPUT);

Serial.begin(9600);
ms.attach(7);


}

void loop() {


if (Serial.available()){
    int val = Serial.read();
    Serial.println(val);
  
if (val==70){
  Serial.println("FORWARD");
  Forward();
}

if (val==76){
  Serial.println("Left");
  Turn_Left();
}
if (val==82){
  Serial.println("Right");
  Turn_Right();
}

if (val==83){
  Serial.println("STOP");
  STOP();

}

if (val==66){
  Serial.println("Backward");
  Backward();
}
if(val ==86){
  digitalWrite(8,HIGH);

}
if(val ==118){
  digitalWrite(8,LOW);

}
}

}

void Turn_Right(){
  digitalWrite(Left_Forward,HIGH);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,HIGH);


}



void Turn_Left(){
  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,HIGH);
  digitalWrite(Left_Backward,HIGH);
  digitalWrite(Right_Backward,LOW);


}

void STOP(){
  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);

}
void Forward(){
  digitalWrite(Left_Forward,HIGH);
  digitalWrite(Right_Forward,HIGH);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);

}

void Backward(){
  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,HIGH);
  digitalWrite(Right_Backward,HIGH);

}