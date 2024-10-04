#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



const int A_forward = 5;
const int A_backward = 3;

const int B_forward = A4;
const int B_backward = A3;

const int C_forward = 9;
const int C_backward = 10;

const int D_forward = A0;
const int D_backward = A1;



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
    // Serial.print("Joystick X: ");
    // Serial.print(data.joystickX);
    // Serial.print(" | Joystick Y: ");
    // Serial.println(data.joystickY);

  int Forward_speed = map(data.joystickY, 340, 710 ,0,255);
  int Backward_speed = map(data.joystickY, 350, 0, 0,255);

  // if(data.joystickY >=340 ){
  //   Serial.print("Forward : ");
  //   Serial.println(Forward_speed);
  //   analogWrite(A_forward,Forward_speed);
  //   analogWrite(A_backward, 0);

  //   analogWrite(B_forward,Forward_speed);
  //   analogWrite(B_backward, 0);

  //   analogWrite(C_forward,Forward_speed);
  //   analogWrite(C_backward, 0);

  //   analogWrite(D_forward,Forward_speed);
  //   analogWrite(D_backward, 0);

  // }

  // else if(data.joystickY < 330 ){
  //   Serial.print("Backward : ");
  //   // Backwar_speed = Backwar_speed;
  //   Serial.println(Backward_speed);
  //   analogWrite(A_forward,0);
  //   analogWrite(A_backward, Backward_speed);

  //   analogWrite(B_forward,0);
  //   analogWrite(B_backward, Backward_speed);

  //   analogWrite(C_forward,0);
  //   analogWrite(C_backward, Backward_speed);

  //   analogWrite(D_forward,0);
  //   analogWrite(D_backward, Backward_speed);



  // }

  // if(data.joystickX > 360){
  //   //left
  //   Serial.println("LEFT");

  //   analogWrite(A_forward,0);
  //   analogWrite(A_backward, 200);

  //   analogWrite(B_forward,0);
  //   analogWrite(B_backward, 200);

  //   analogWrite(C_forward,200);
  //   analogWrite(C_backward, 0);

  //   analogWrite(D_forward,200);
  //   analogWrite(D_backward, 0);



  // }

  // else if(data.joystickX < 350){
  //   //Right
  //   Serial.println("Right");
  //       analogWrite(A_forward,200);
  //   analogWrite(A_backward, 0);

  //   analogWrite(B_forward,0);
  //   analogWrite(B_backward, 200);

  //   analogWrite(C_forward,0);
  //   analogWrite(C_backward, 200);

  //   analogWrite(D_forward,0);
  //   analogWrite(D_backward, 200);
  
  // }
  // else{
  //   //stop
  //       analogWrite(A_forward,0);
  //   analogWrite(A_backward, 0);

  //   analogWrite(B_forward,0);
  //   analogWrite(B_backward, 0);

  //   analogWrite(C_forward,0);
  //   analogWrite(C_backward, 0);

  //   analogWrite(D_forward,0);
  //   analogWrite(D_backward, 0);
  // }


  }
}
