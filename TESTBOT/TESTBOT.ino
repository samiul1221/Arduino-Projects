/*
13 - ENA
12- INA 1 RF
14 - INA 2 RB
27 - INA 3  LB
26 - INA 4 LF
25 - ENB

23 - Red
19 - Green
18 - Blue
15 - Switch

Bluetooth Rc controller App
FS - forward stop
BS - Backward stop
LS - Left stop
RS - Right Stop

*/
// #MaxSpeed 255
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int ENA = 13, RF =12, RB = 14, LB = 27, LF = 26, ENB = 25, Switch = 15, R = 23, G =19, B=18;

void setup() {
  // put your setup code here, to run once:
    analogReadResolution(10);
    Serial.begin(115200);
     SerialBT.begin("ESP32test"); //Bluetooth device name

    pinMode(ENA,OUTPUT);
    pinMode(RB,OUTPUT);
    pinMode(RF,OUTPUT);
    pinMode(LF,OUTPUT);
    pinMode(LB,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(R,OUTPUT);
    pinMode(G,OUTPUT);
    pinMode(B,OUTPUT);
    pinMode(Switch,INPUT);

}

void loop() {
 if (SerialBT.available()) {
   Serial.write(SerialBT.read());
  //  Serial.;
   
 }


}
