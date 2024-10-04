#include <SPI.h>
#include <RF24.h>

// Define CE and CSN pins
#define CE_PIN 7
#define CSN_PIN 8

// Define joystick pins
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for communication
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  
  // Initialize the NRF24L01 module
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {}  // Hold in infinite loop
  }
  
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);  // You can set this higher depending on the distance
  radio.stopListening();  // Put the radio in transmit mode
}

void loop() {
  // Read joystick values
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);
  
  // Create a data structure to hold the joystick values
  struct JoystickData {
    int x;
    int y;
  };
  
  JoystickData data = {xValue, yValue};
  
  // Send the data
  bool report = radio.write(&data, sizeof(data));
  
  if (report) {
    Serial.println("Transmission successful");
  } else {
    Serial.println("Transmission failed");
  }
  
  delay(100);  // Small delay to not flood the receiver
}