
//edison science corner

#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
float Kp = .2; 
float Ki = 0;
float Kd =.1;
int P;
int I;
int D;
int lastError = 0;
boolean onoff = false;

const uint8_t maxspeeda = 250;
const uint8_t maxspeedb = 250;
const uint8_t basespeeda = 100;
const uint8_t basespeedb = 100;


int mode = 8;
int aphase = 9;
int aenbl = 6;
int bphase = 5;
int benbl = 3;


int buttoncalibrate = 17;//pin A3
int buttonstart = 2;

void setup() {
  Serial.begin(9600);
  qtr.setTypeRC();
 
  qtr.setSensorPins((const uint8_t[]){10, 11, 12, 14, 15, 16, 18, 19}, SensorCount);
  qtr.setEmitterPin(7);//LEDON PIN
   pinMode(mode, OUTPUT);
  pinMode(aphase, OUTPUT);
  pinMode(aenbl, OUTPUT);
  pinMode(bphase, OUTPUT);
  pinMode(benbl, OUTPUT);
  digitalWrite(mode, HIGH);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);

  boolean Ok = false;
  while (Ok == false) { 
    if(digitalRead(buttoncalibrate) == HIGH) {
      calibration(); 
      Ok = true;
    }
  }
  forward_brake(0, 0);
}

void calibration() {
  digitalWrite(4, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(4, LOW);
}

void loop() {
  if(digitalRead(buttonstart) == HIGH) {
    onoff =! onoff;
    if(onoff = true) {
      delay(1000);
    }
    else {
      delay(50);
    }
  }
  if (onoff == true) {
    PID_control();
  }
  else {
    forward_brake(0,0);
  }
}
void forward_brake(int posa, int posb) {
  digitalWrite(aphase, LOW);
  digitalWrite(bphase, HIGH);
  analogWrite(aenbl, posa);
  analogWrite(benbl, posb);
}
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = 3500 - position;

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P*Kp + I*Ki + D*Kd;
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 
  forward_brake(motorspeeda, motorspeedb);
}
