#include <Servo.h>

// Create a servo object
Servo motor;

void setup() {
  // Attach the servo to pin 9
  motor.attach(9);
}

void loop() {
  // Run motor in one direction
  runMotorClockwise();
  delay(5000); // Run for 5 seconds

  // Stop motor
  stopMotor();
  delay(1000); // Delay 1 second
  
  // // Run motor in the opposite direction
  runMotorCounterClockwise();
  delay(5000); // Run for 5 seconds

  // // Stop motor
  stopMotor();
  delay(1000); // Delay 1 second
}

void runMotorClockwise() {
  // Set the motor position to clockwise direction
  motor.writeMicroseconds(1000); // Adjust the value based on your ESC and motor
}

void runMotorCounterClockwise() {
  // Set the motor position to counter-clockwise direction
  motor.writeMicroseconds(1700); // Adjust the value based on your ESC and motor
}

void stopMotor() {
  // Stop the motor
  motor.writeMicroseconds(1500); // Adjust the value based on your ESC and motor
}
