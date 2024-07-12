
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int time;
int distance;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("The distance : ");
  pinMode(6,OUTPUT);
  pinMode(7,INPUT);
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  digitalWrite(6,HIGH);
  delayMicroseconds(10);
  digitalWrite(6,LOW);
  
  delayMicroseconds(5);

  digitalWrite(6,HIGH);
  delayMicroseconds(10);

  time = pulseIn(7,HIGH);

  distance = (0.0343*time)/2;
  Serial.print("The distance is : ");
  Serial.println(distance);
  // print the number of seconds since reset:
}

