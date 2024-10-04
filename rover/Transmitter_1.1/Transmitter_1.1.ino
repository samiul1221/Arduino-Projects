#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const int joyX = A0;  // Joystick X-axis connected to A0
const int joyY = A1;  // Joystick Y-axis connected to A1

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  int Xval = analogRead(joyX);
  int Yval = analogRead(joyY);

  char controlChar = 'S'; // Default to 'S' for stop

  if (Xval > 370) {
    controlChar = 'L';
  }
  else if (Xval < 300) {
    controlChar = 'R';
  }
  else if (Yval > 350) {
    controlChar = 'U';
  }
  else if (Yval < 300) {
    controlChar = 'D';
  }

  radio.write(&controlChar, sizeof(char));
  
  Serial.print(controlChar);
  Serial.print(" : X = ");
  Serial.print(Xval);
  Serial.print(", Y = ");
  Serial.println(Yval);

  delay(100);
}