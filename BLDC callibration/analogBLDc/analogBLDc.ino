// Define motor control pin
#define MOTOR_PIN 9

void setup() {
  // Initialize motor control pin
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // Run motor in one direction
  runMotorClockwise();
  delay(2000); // Run for 5 seconds

  // Stop motor
  stopMotor();
  delay(2000); // Delay 1 second
  analogWrite(MOTOR_PIN, 50);
  delay(5000);
  
  // Run motor in the opposite direction
  runMotorCounterClockwise();
  delay(5000); // Run for 5 seconds

  // // Stop motor
  stopMotor();
  delay(1000); // Delay 1 second
}

void runMotorClockwise() {
  analogWrite(MOTOR_PIN, 200); // Adjust PWM value to control speed (0-255)
}

void runMotorCounterClockwise() {
  analogWrite(MOTOR_PIN, 105); // Adjust PWM value to control speed (0-255) in opposite direction
}

void stopMotor() {
  analogWrite(MOTOR_PIN, 0); // Stop motor
}
