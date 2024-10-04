#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the RF24 radio object with CE and CSN pins
RF24 radio(7, 8); // CE is pin 7, CSN is pin 8

// Define a unique address for communication (make sure the receiver has the same address)
const byte address[6] = "00001";

struct Data_Package {
  int joystickX;
  int joystickY;
};

Data_Package data; // Struct to hold the data

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address); // Set the address for the pipe
  radio.setPALevel(RF24_PA_MIN);  // Set the power level to low to reduce current draw
  radio.stopListening();          // Transmitter mode
}

void loop() {
  // Read joystick values from analog pins
  data.joystickX = analogRead(A0); // X-axis
  data.joystickY = analogRead(A1); // Y-axis

  // Send data package over nRF24L01
  radio.write(&data, sizeof(Data_Package));
  // data.joystickX = (data.joystickX*1024)/710;
  // For debugging purpose
  Serial.print("X: ");
  Serial.print(data.joystickX);
  Serial.print(" | Y: ");
  Serial.println(data.joystickY);

  delay(100); // Send every 100 milliseconds
}
