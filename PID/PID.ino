#include<QTRSensors.h>
QTRSensors  qtr;
short int Sensor = 8 //number of ir sensors 



float Kp = 0.5;
float Ki = 0;
float Kd = 0.8;


float P, I, D, error;
float Last_Error = 0;
float PID_Value = 0;
const uint8_t Maxspeed = 255;
const uint8_t Basespeed = 150;


void PID_Algo();

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  

}

void PID_Algo(){
  P = error;
  I = I + error;
  D = error - Last_Error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  Last_Error = error;
}
