/*Obstacle avoidance Robot car.
  created by the SriTu Tech team.
  Read the code below and use it for any of your creation
*/
#include <AFMotor.h>
#include <Servo.h>
#define Speed 180
#define Trig A0
#define Echo A1
#define spoint 90
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(10);
  start();
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

}

void loop() {
  distance = ultrasonic();
  if (distance <= 5) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      turnleft();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      turnright();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void turnleft() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void turnright() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
int leftsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int rightsee() {
  servo.write(150);
  delay(800);
  Right = ultrasonic();
  return Right;
}

int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void start() {
  delay(3000);
  for (int a = 0; a < 4; a++) {
    servo.write(spoint);
    delay(50);
    servo.write(40);
    delay(50);
    servo.write(90);
    delay(50);
    servo.write(spoint);
  }
}
