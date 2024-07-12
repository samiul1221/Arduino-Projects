/*
13 - ENA (Right)
12- INA 1 RF
14 - INA 2 RB
27 - INA 3  LB
26 - INA 4 LF
25 - ENB (Left)

23 - Red
19 - Green
18 - Blue
15 - Switch

Bluetooth Rc controller App
F - forward stop
B - Backward stop
L - Left stop
R - Right Stop
RI - North East
FG - North West
BH - South West
BJ - South East
x - triangle
V - Horn
U - Back Light
W - Front Light
*/
// #MaxSpeed 255
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ENA = 13, RF =12, RB = 14, LB = 27, LF = 26, ENB = 25, Switch = 15, B =33, G=32,speed=170,CE = 4,CSN =5;
String s;

RF24 radio(CE, CSN); // CE, CSN
const byte address[6] = "00001";

void led( int Green=200, int Blue=200);


void setup() {
    analogReadResolution(10);
    Serial.begin(115200);
    
  // Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();
    pinMode(ENA,OUTPUT);
    pinMode(RB,OUTPUT);
    pinMode(RF,OUTPUT);
    pinMode(LF,OUTPUT);
    pinMode(LB,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(G,OUTPUT);
    pinMode(B,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(Switch,INPUT);

}
bool blink = 0;

void loop() {
  // // led(0,255);
  // digitalWrite(B,HIGH);
  //     digitalWrite(G,LOW);
if (radio.available()) {
  // led(150,150);
    digitalWrite(G,HIGH);
    delay(500);
    digitalWrite(G,LOW);






    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    // char up[32] = "UP"
    
    // int receivedInt; // Variable to store the received integer
    // radio.read(&receivedInt, sizeof(receivedInt)); // Read the integer from the NRF module
    // Serial.println(receivedInt); // Print the received integer
    
    
    if (strcmp(text, "UP") == 0) {
      Serial.println("UP");
      forward();



    }
    
    else if (strcmp(text, "DOWN") == 0) {
      Serial.println("DOWN");
      backward();
    }

    else if (strcmp(text, "RIGHT") == 0) {
      Hardright();
      Serial.println("RIGHT");
    }


    else if (strcmp(text, "LEFT") == 0) {
      Hardleft();
      Serial.println("LEFT");
      led(200,100);
    }

else{
      stop();
      led(0,0);


}
    
  }




}
void forward(){
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(RF,HIGH);
  digitalWrite(LF,HIGH);
  digitalWrite(RB,LOW);
  digitalWrite(LB,LOW);
  led(0,200);

}

void backward(){
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,HIGH);
  led(200,0);
}


void Softleft(){
  analogWrite(ENA,0);
  analogWrite(ENB,speed);
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,HIGH);
  blink = 0;
}

void Softright(){
  analogWrite(ENA,speed);
  analogWrite(ENB,0);
  digitalWrite(RF,LOW);
  digitalWrite(LF,LOW);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,HIGH);
  blink = 0;
}

void Hardleft(){
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(RF,HIGH);
  digitalWrite(LF,LOW);
  digitalWrite(RB,LOW);
  digitalWrite(LB,HIGH);
  led(200,100);
}


void Hardright(){
  analogWrite(ENA,speed);
  analogWrite(ENB,speed);
  digitalWrite(RF,LOW);
  digitalWrite(LF,HIGH);
  digitalWrite(RB,HIGH);
  digitalWrite(LB,LOW);
  led(100,200);

}

void stop(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  blink = 0;

}

void led(int Green, int Blue){
  // analogWrite(R,Red);
  analogWrite(G,Green);
  analogWrite(B,Blue);
}
