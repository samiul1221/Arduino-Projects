#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Receiver

// Define the RF24 radio object with CE and CSN pins
RF24 radio(7, 8); // CE is pin 7, CSN is pin 8

// Define the address for communication (must match the transmitter)
const byte address[6] = "00001";

struct Data_Package {
  int joystickX;
  int joystickY;
};

Data_Package data; // Struct to hold the received data

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // Set the address for the pipe
  radio.setPALevel(RF24_PA_MIN);     // Set the power level to low to reduce current draw
  radio.startListening();            // Receiver mode
}

void loop() {
  // Check if data is available to read
  if (radio.available()) {
    // Read the data into the data package
    radio.read(&data, sizeof(Data_Package));

    // Print received values
    Serial.print("Joystick X: ");
    Serial.print(data.joystickX );
    Serial.print(" | Joystick Y: ");
    Serial.println(data.joystickY);
  }
}
