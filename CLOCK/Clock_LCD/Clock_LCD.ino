// sketch created by Teach Me Something
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
// Set the LCD address to 0x27 by Teach Me Something
LiquidCrystal_I2C lcd(0x3F, 16, 2);   
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time t;

void setup()
{
  lcd.begin();
  lcd.clear();
  Serial.begin(9600);

rtc.begin();
rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
rtc.setTime(20, 10, 10);     // Set the time to 12:00:00 (24hr format)
rtc.setDate(9, 3, 2021); 
}

void loop()
{
 rtc.getTime();
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr());
  Serial.println(rtc.getTimeStr());
  lcd.setCursor(0,1);
  lcd.println(rtc.getTimeStr());
  delay(1000);
}
