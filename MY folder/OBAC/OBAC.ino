#include "NewPing.h"
#include<Servo.h>

#define TP 9
#define EP 8
void Forward();
void Turn_Right();
void Turn_Left();
void STOP();
int Left_Forward = 3;
int Left_Backward = 2;

int Right_Forward = 4;
int Right_Backward = 5;

Servo ms;

NewPing sonar(TP,EP,400);
float distance;
void setup() {
pinMode(Left_Backward,OUTPUT);
pinMode(Left_Forward,OUTPUT);
pinMode(Right_Forward,OUTPUT);
pinMode(Right_Backward,OUTPUT);


Serial.begin(9600);
ms.attach(7);


}

void loop() {
  if(sonar.ping_cm() >15){

  Forward();
  }

  else if (sonar.ping_cm()<=15){
  STOP();
  int L_dist = 0;
  int R_dist = 0;
  for (int i =0;i<=90;i++){
    ms.write(i);
    delay(20);
    R_dist += sonar.ping_cm();
  }
  for (int i =91;i<=180;i++){
    ms.write(i);
    delay(20);
    L_dist += sonar.ping_cm();
  }
  delay(1000);
  ms.write(90);
  if(L_dist>=R_dist){
    Turn_Left();
    STOP();
    if (sonar.ping_cm()>15){
      digitalWrite(Left_Forward,HIGH);
  digitalWrite(Right_Forward,HIGH);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);

    }
  }

  if(L_dist>=R_dist){
    Turn_Left();
    STOP();
  if (sonar.ping_cm()>15){
  digitalWrite(Left_Forward,HIGH);
  digitalWrite(Right_Forward,HIGH);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);



    }
  }
  
  }


}

void Turn_Right(){
  digitalWrite(Left_Forward,HIGH);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,HIGH);

  delay(500);

  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);
  ms.write(90);
}



void Turn_Left(){
  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,HIGH);
  digitalWrite(Left_Backward,HIGH);
  digitalWrite(Right_Backward,LOW);

  delay(500);

  digitalWrite(Left_Forward,LOW);
  digitalWrite(Right_Forward,LOW);
  digitalWrite(Left_Backward,LOW);
  digitalWrite(Right_Backward,LOW);
  ms.write(90);

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