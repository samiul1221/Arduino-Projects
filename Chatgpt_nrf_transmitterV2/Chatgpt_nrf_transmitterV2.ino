#include <Wire.h>
#include <MPU6050.h>
#include <RF24.h>

// MPU6050
MPU6050 mpu;
int16_t ax, ay, az;

// NRF24L01
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// Joystick
const int VRx = A0;
const int VRy = A1;

// LEDs
const int redLED = 5;
const int greenLED = 6;

// Push Buttons
const int button1Pin = 2;
const int button2Pin = 3;

// Mode control
bool mpuMode = false;

struct DataPacket {
  char direction;
  int speed;
};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();
  
  // Initialize NRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX); // Set power level to maximum
  radio.setDataRate(RF24_2MBPS); // Set data rate to 2 Mbps
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
  int speed = 0;
  if (ax > 15000) {
    direction = 'R';
    speed = map(ax, 15000, 32767, 0, 255);
  } else if (ax < -15000) {
    direction = 'L';
    speed = map(ax, -32768, -15000, 0, 255);
  } else if (ay > 15000) {
    direction = 'U';
    speed = map(ay, 15000, 32767, 0, 255);
  } else if (ay < -15000) {
    direction = 'D';
    speed = map(ay, -32768, -15000, 0, 255);
  }
  
  // Transmit direction and speed
  DataPacket data = { direction, speed };
  radio.write(&data, sizeof(data));
}

void transmitJoystick() {
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);
  
  // Calculate direction based on joystick position
  char direction = 'S';
  int speed = 0;
  if (xValue > 800) {
    direction = 'R';
    speed = map(xValue, 800, 1023, 0, 255);
  } else if (xValue < 200) {
    direction = 'L';
    speed = map(xValue, 0, 200, 255, 0);
  } else if (yValue > 800) {
    direction = 'U';
    speed = map(yValue, 800, 1023, 0, 255);
  } else if (yValue < 200) {
    direction = 'D';
    speed = map(yValue, 0, 200, 255, 0);
  }
  
  // Transmit direction and speed
  DataPacket data = { direction, speed };
  radio.write(&data, sizeof(data));
}
