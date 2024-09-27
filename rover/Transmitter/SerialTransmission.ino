#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//SCK - 13
//MISO - 12
//MOSI - 11
RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(9600);
}

void loop() {
 
  char data = Serial.read();

  if(data=='L'){
    const char Left[] = "LEFT";
    radio.write(&Left, sizeof(Left));
    Serial.print("Left");

    
  }
  else if(data == 'R'){
    const char right[] = "RIGHT";
      radio.write(&right, sizeof(right));
    Serial.print("Right");

  }


    else if(data == 'F'){
    const char up[] = "UP";
      radio.write(&up, sizeof(up));
    Serial.print("Forward");

  }

      else if(data =='B'){
    const char down[] = "DOWN";
    radio.write(&down, sizeof(down));
    Serial.print("Backward");
  }
  else{
    const char stop[] = "stop";
    radio.write(&stop, sizeof(stop));


  }
  delay(100);
}