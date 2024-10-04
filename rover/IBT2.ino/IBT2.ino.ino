// Pin definitions
const int RPWM = 5;  // Pin connected to RPWM on IBT-2 (Forward)
const int LPWM = 3;  // Pin connected to LPWM on IBT-2 (Reverse)
const int R_EN = 7;  // Pin connected to R_EN on IBT-2
const int L_EN = 8;  // Pin connected to L_EN on IBT-2

void setup() {
  // Set the control pins as outputs
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  // Enable both directions
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
}

void loop() {
  // Move motor forward
  analogWrite(RPWM, 200);  // Set speed (0-255), closer to 255 = faster
  analogWrite(LPWM, 0);    // Set reverse pin to 0 (no reverse motion)
  delay(2000);             // Run forward for 2 seconds

  // Stop motor
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(1000);             // Stop for 1 second

  // Move motor reverse
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 200);  // Set speed for reverse direction
  delay(2000);             // Run reverse for 2 seconds

  // Stop motor again
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(1000);             // Stop for 1 second
}
