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
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
 
  int u = digitalRead(6);
  int l = digitalRead(4);
  int d = digitalRead(5);
  int r = digitalRead(3);
  int potVal = 255;
  // Serial.println(potVal);

  
  // // Convert the integer to a byte array
  // byte byteArray[sizeof(int)];
  // memcpy(byteArray, &potVal, sizeof(int));

  // // Send the byte array
  // radio.write(byteArray, sizeof(byteArray));


  if(l){
    const char Left[] = "LEFT";
    radio.write(&Left, sizeof(Left));
    Serial.print("L : ");
    Serial.println(l);

    
  }
  else if(r){
    const char right[] = "RIGHT";
      radio.write(&right, sizeof(right));
    Serial.print("R : ");
    Serial.println(r);

  }


    else if(u){
    const char up[] = "UP";
      radio.write(&up, sizeof(up));
    Serial.print("U : ");
    Serial.println(u);

  }

      else if(d){
    const char down[] = "DOWN";
    radio.write(&down, sizeof(down));
    Serial.print("D : ");
    Serial.println(d);

  }
  else{
    const char stop[] = "stop";
    radio.write(&stop, sizeof(stop));


  }
  delay(100);
}