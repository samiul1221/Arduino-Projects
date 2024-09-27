#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//SCK - 13
//MISO - 12
//MOSI - 11
RF24 radio(7, 8); // CE, CSN
const int joyX = A0;  // Joystick X-axis connected to A0
const int joyY = A1;  // Joystick Y-axis connected to A1

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  // pinMode(6,INPUT);
  // pinMode(5,INPUT);
  // pinMode(4,INPUT);
  // pinMode(3,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
}

void loop() {
 
  int Xval = analogRead(joyX);
  int Yval = analogRead(joyY);



  if(Xval>370){
    const char Left[] = "LEFT";
    radio.write(&Left, sizeof(Left));
    Serial.print("L : ");
    Serial.println(Xval);

    
  }
  else if(Xval<300){
    const char right[] = "RIGHT";
      radio.write(&right, sizeof(right));
    Serial.print("R : ");
    Serial.println(Xval);

  }


    else if(Yval >350){
    const char up[] = "UP";
      radio.write(&up, sizeof(up));
    Serial.print("U : ");
    Serial.println(Yval);

  }

      else if(Yval < 300){
    const char down[] = "DOWN";
    radio.write(&down, sizeof(down));
    Serial.print("D : ");
    Serial.println(Yval);

  }
  else{
    const char stop[] = "stop";
    radio.write(&stop, sizeof(stop));


  }
  delay(100);
}