/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

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
  // radio.
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);

  if(text[0] == 'U' || text[0] == "U"){
  analogWrite(A0, 200);  // Set speed (0-255), closer to 255 = faster
  analogWrite(A1, 0); 
  }

   if( text[0]=='D' || text[0] == "D"){
  analogWrite(A0, 0);  // Set speed (0-255), closer to 255 = faster
  analogWrite(A1, 200); 
  }
  else{
      analogWrite(A0, 0);  // Set speed (0-255), closer to 255 = faster
  analogWrite(A1, 0); 
  }



  }


}
