#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.stopListening();

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
}

void loop() {
  float xVal = readAccelX();
  float yVal = readAccelY();

  char command;

  if (xVal > 5) {
    command = 'L'; // Left
  } else if (xVal < -5) {
    command = 'R'; // Right
  } else if (yVal < -5) {
    command = 'U'; // Forward
  } else if (yVal > 5) {
    command = 'D'; // Backward
  } else {
    command = 'S'; // Stop
  }

  radio.write(&command, sizeof(command));

  delay(100);
}

float readAccelX() {


    sensors_event_t event, g, temp;
  mpu.getEvent(&event, &g, &temp);
  return event.acceleration.x;
}

float readAccelY() {

  sensors_event_t event, g, temp;
  mpu.getEvent(&event, &g, &temp);
  return event.acceleration.y;
}
