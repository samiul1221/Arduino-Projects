#include<Servo.h>
#include "NewPing.h"

#define Trig_Pin 2
#define Echo_Pin 3
#define Max_distance 400

NewPing my_sonar(Trig_Pin,Echo_Pin,Max_distance);
Servo my_servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  my_servo.attach(8);
  Serial.begin(9600);


}

int distance;
void loop() {
  // put your main code here, to run repeatedly:

  distance = my_sonar.ping_cm();

  for (int i= 0; i<=180;i++){
    my_servo.write(i);
    delay(25);
      Serial.println(distance);

  }

  for (int i= 180; i>=0;i--){
    my_servo.write(i);
    delay(25);
      Serial.println(distance);

  }

  // for (int i=5;i<=11;i++){
  //   digitalWrite(i,HIGH);
  //   delay(distance);
  // }
  // delay(distance);
  // for (int i=5;i<=11;i++){
  //   digitalWrite(i,LOW);
  //   delay(distance);
  // }
 


}
