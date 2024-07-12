#include <QTRSensors.h>
 
#define rightMotor1  7
#define rightMotor2  8
#define leftMotor1  10
#define leftMotor2  9
#define rightMotorPWM 6
#define leftMotorPWM  5

#define NUM_SENSORS 8 // number of sensors used
#define NUM_SAMPLES_PER_SENSOR 4 // average 4 analog samples per sensor reading
#define EMITTER_PIN 2 // emitter is controlled by digital pin 2

#define Kp 0.038 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 0.76// experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define speedturn 150
#define MaxSpeed 255// max speed of the robot
#define BaseSpeed 80 // this is the speed at which the motors should spin when the robot is perfectly on the line

 
// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {A0, A1, A2, A3, A4, A5,3,4}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
int lastError = 0;
unsigned int sensors[8];

 
void setup()
{
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
 delay(500);
 pinMode(13, OUTPUT);
 digitalWrite(13, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
 for (int i = 0; i < 200; i++) // make the calibration take about 10 seconds
 {
 qtra.calibrate(); // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
 }
 digitalWrite(13, LOW); // turn off Arduino's LED to indicate we are through with calibration
 
 // print the calibration minimum values measured when emitters were on
 Serial.begin(9600);
 for (int i = 0; i < NUM_SENSORS; i++)
 {
 Serial.print(qtra.calibratedMinimumOn[i]);
 Serial.print(' ');
 }
 Serial.println();
 
 // print the calibration maximum values measured when emitters were on
 for (int i = 0; i < NUM_SENSORS; i++)
 {
 Serial.print(qtra.calibratedMaximumOn[i]);
 Serial.print(' ');
 }
 Serial.println();
 Serial.println();
 delay(1000);
}
 
 
void loop()
{
 // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
 // To get raw sensor values, call:
 // qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
 unsigned int position = qtra.readLine(sensorValues);
 
 // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
 // 1000 means minimum reflectance, followed by the line position
 for (unsigned char i = 0; i < NUM_SENSORS; i++)
 {
 Serial.print(sensorValues[i]);
 Serial.print('\t');
 }
 //Serial.println(); // uncomment this line if you are using raw values
 Serial.println(position); // comment this line out if you are using raw values
 
 delay(250);




 position = qtra.readLine(sensorValues);

  if (position > 6700) {
    move(1, speedturn, 1);//motor derecho hacia adelante
    move(0, speedturn, 0);//motor izquierdo hacia adelante
    return;
  }
  if (position < 300) {
    move(1, speedturn, 0);//motor derecho hacia adelante
    move(0, speedturn, 1);//motor izquierdo hacia adelante
    return;
  }

  int error = position - 3500;
  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;

  int rightMotorSpeed = BaseSpeed + motorSpeed;
  int leftMotorSpeed = BaseSpeed - motorSpeed;

  if (rightMotorSpeed > MaxSpeed ) rightMotorSpeed = MaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > MaxSpeed ) leftMotorSpeed = MaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0)rightMotorSpeed = 0;
  if (leftMotorSpeed < 0)leftMotorSpeed = 0;

  move(1, rightMotorSpeed, 1);//motor derecho hacia adelante
  move(0, leftMotorSpeed, 1);//motor izquierdo hacia adelante
}


void move(int motor, int speed, int direction) {

  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  if (direction == 0) {
    inPin1 = LOW;
    inPin2 = HIGH;
  }

  if (motor == 0) {
    digitalWrite(leftMotor1, inPin1);
    digitalWrite(leftMotor2, inPin2);
    analogWrite(leftMotorPWM, speed);
  }
  if (motor == 1) {
    digitalWrite(rightMotor1, inPin1);
    digitalWrite(rightMotor2, inPin2);
    analogWrite(rightMotorPWM, speed);
  }
}
