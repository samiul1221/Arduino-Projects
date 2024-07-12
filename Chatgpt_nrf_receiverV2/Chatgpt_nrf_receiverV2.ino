#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ENA = 13, RF = 12, RB = 14, LB = 27, LF = 26, ENB = 25, Switch = 15, B = 33, G = 32, CE = 4, CSN = 5;
String s;

RF24 radio(CE, CSN); // CE, CSN
const byte address[6] = "00001";
bool blink = false;

struct DataPacket {
  char direction;
  int speed;
};

void led(int Green = 200, int Blue = 200);

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); // Set power level to maximum
  radio.setDataRate(RF24_2MBPS); // Set data rate to 2 Mbps
  radio.startListening();

  pinMode(ENA, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(Switch, INPUT);
}

void loop() {
  if (radio.available()) {
    DataPacket data;
    radio.read(&data, sizeof(data));
    Serial.print("Direction: ");
    Serial.print(data.direction);
    Serial.print(" | Speed: ");
    Serial.println(data.speed);

    int receivedSpeed = data.speed;

    switch (data.direction) {
      case 'U':
        forward(receivedSpeed);
        break;
      case 'D':
        backward(receivedSpeed);
        break;
      case 'R':
        Hardright(receivedSpeed);
        break;
      case 'L':
        Hardleft(receivedSpeed);
        break;
      default:
        stop();
        led(0, 0);
        break;
    }
  }
}

void forward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(RF, HIGH);
  digitalWrite(LF, HIGH);
  digitalWrite(RB, LOW);
  digitalWrite(LB, LOW);
  led(255, 0);
}

void backward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(RB, HIGH);
  digitalWrite(LB, HIGH);
  led(0, 200);
}

void Hardleft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(RF, HIGH);
  digitalWrite(LF, LOW);
  digitalWrite(RB, LOW);
  digitalWrite(LB, HIGH);
  led(200, 100);
}

void Hardright(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(RF, LOW);
  digitalWrite(LF, HIGH);
  digitalWrite(RB, HIGH);
  digitalWrite(LB, LOW);
  led(100, 200);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  blink = 0;
}

void led(int Green, int Blue) {
  analogWrite(G, Green);
  analogWrite(B, Blue);
}
