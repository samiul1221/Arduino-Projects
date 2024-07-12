#define rightMotor1  7//7
#define rightMotor2  8//8
#define leftMotor1  10//10
#define leftMotor2  9//9
#define rightMotorPWM 6
#define leftMotorPWM  5//5

#include <QTRSensors.h>



#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5,3,4}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

#define Kp 0.2 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 4// experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 

#define speedturn 180
#define MaxSpeed 255// max speed of the robot
#define BaseSpeed 255 // this is the speed at which the motors should spin when the robot is perfectly on the line

void setup()
{


  delay(500);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

int lastError = 0;
unsigned int sensors[8];
void loop()
{

  unsigned int position = qtrrc.readLine(sensorValues);
  position = qtrrc.readLine(sensorValues);

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

