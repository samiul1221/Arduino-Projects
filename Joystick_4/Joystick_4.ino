#include<Servo.h>

#define ESC_PIN 2

Servo esc;
int decision = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop() 
{
int xVal = analogRead(A0);
int yVal = analogRead(A1);
// Serial.print("X : ");
// Serial.print(xVal);

// Serial.print("      Y : ");
// Serial.print(yVal);

// Serial.print("\n");

if (xVal>900 && 490<yVal<520){
// Serial.println("Right");
decision = 1;

}


else if (xVal<10 && 490<yVal<520){
// Serial.println("Left");
decision = 2;

}

else if (yVal>900 && 490<xVal<520){
// Serial.println("Down");
decision = 3;

}


else if (yVal<10 && 490<xVal<520){
// Serial.println("UP");
decision = 4;

}
Serial.println(decision);

}