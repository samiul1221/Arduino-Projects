#include <SPI.h>
#include <RF24.h>

// Define CE and CSN pins
#define CE_PIN 7
#define CSN_PIN 8

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
  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);  // You can set this higher depending on the distance
  radio.startListening();  // Put the radio in receive mode
}

void loop() {
  if (radio.available()) {
    struct JoystickData {
      int x;
      int y;
    };
    
    JoystickData data;
    radio.read(&data, sizeof(data));
    
    // Print the received joystick values
    Serial.print("X: ");
    Serial.print(data.x);
    Serial.print(" Y: ");
    Serial.println(data.y);
  }
}