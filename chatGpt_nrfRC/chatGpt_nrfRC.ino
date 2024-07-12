#include <Wire.h>
#include <MPU6050.h>
#include <RF24.h>

// MPU6050
MPU6050 mpu;

// NRF24L01
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// Joystick
const int VRx = A0;
const int VRy = A1;

// LEDs
const int redLED = 4;
const int greenLED = 5;

// Push Buttons
const int button1Pin = 2;
const int button2Pin = 3;

// Mode control
bool mpuMode = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();
  
  // Initialize NRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  
  // Initialize Joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  
  // Initialize LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // Initialize Push Buttons
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  
  // Initial LED state
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
}

void loop() {
  // Check push button state
  if (digitalRead(button1Pin) == LOW) {
    mpuMode = !mpuMode;
    delay(300); // Debounce delay
  }
  
  if (mpuMode) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    transmitMPU6050();
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    transmitJoystick();
  }
}

void transmitMPU6050() {
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Calculate direction based on acceleration
  char direction = 'S';
  if (ax > 15000) direction = 'R';
  else if (ax < -15000) direction = 'L';
  else if (ay > 15000) direction = 'U';
  else if (ay < -15000) direction = 'D';
  
  // Transmit direction
  radio.write(&direction, sizeof(direction));
}

void transmitJoystick() {
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);
  
  // Calculate direction based on joystick position
  char direction = 'S';
  if (xValue > 800) direction = 'R';
  else if (xValue < 200) direction = 'L';
  else if (yValue > 800) direction = 'U';
  else if (yValue < 200) direction = 'D';
  
  // Transmit direction
  radio.write(&direction, sizeof(direction));
}
