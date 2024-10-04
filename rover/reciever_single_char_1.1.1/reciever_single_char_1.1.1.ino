#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char controlChar;
    radio.read(&controlChar, sizeof(controlChar));
    Serial.print("Received: ");
    Serial.println(controlChar);

    switch(controlChar) {
      case 'U':
        moveForward();
        break;
      case 'D':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
      default:
        stopMotors();
        break;
    }
  }
}

void moveForward() {
  analogWrite(A0, 200);
  analogWrite(A1, 0);
}

void moveBackward() {
  analogWrite(A0, 0);
  analogWrite(A1, 200);
}

void turnLeft() {
  analogWrite(A0, 100);
  analogWrite(A1, 0);
}

void turnRight() {
  analogWrite(A0, 0);
  analogWrite(A1, 100);
}

void stopMotors() {
  analogWrite(A0, 0);
  analogWrite(A1, 0);
}