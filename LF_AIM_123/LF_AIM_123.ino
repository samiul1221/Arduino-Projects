#define MS 12 // Middle Sensor
#define LS 13 // Left sensor
#define RS 11 // Right sensor
#define LED 6 // The LED
#define ES 7 // back on back of bot to check the end point
#define LM1 2 // left forward motor
#define LM2 3 // left backward motor
#define RM1 4 // right forward motor
#define RM2 5 // right backward motor
void setup()
{
Serial.begin(9600);
pinMode(MS, INPUT);
pinMode(LS, INPUT);
pinMode(ES, INPUT);
pinMode(RS, INPUT);
pinMode(LM1, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(LM2, OUTPUT);
pinMode(RM1, OUTPUT);
pinMode(RM2, OUTPUT);

}
void loop()
{
if(digitalRead(MS)) // Middle Sensor On Line
{
if(!digitalRead(LS) && !digitalRead(RS)) //LS and RS not on line
{
Serial.println("move forward");
digitalWrite(LM1, LOW);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
digitalWrite(LED, LOW);

}
else if(digitalRead(LS) && !digitalRead(RS)) //Sharp Left
{
Serial.println("Sharp Left");
digitalWrite(LM1, LOW);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, LOW);
digitalWrite(LED, LOW);
delay(500); // bhai yaha se time change karke try kariyo perfet turn kitne time bad le rha h
// Stop();  // stop nhi kiya kyuki ghumke apne ap black strip detect karegi to rauk sakta hagar chahe

}
else if(!digitalRead(LS) && digitalRead(RS)) //Sharp Right
{
Serial.println("Sharp Right");
digitalWrite(LM1, HIGH);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
digitalWrite(LED, LOW);
delay(500); // bhai yaha se time change karke try kariyo perfet turn kitne time bad le rha h
// Stop();  // stop nhi kiya kyuki ghumke apne ap black strip detect karegi to rauk sakta hagar chahe


}
else if(digitalRead(LS) && digitalRead(RS) && !digitalRead(ES))
{
// all 3 front sensor in black strip 
Serial.println("Sharp Right"); // Always Right in T point
digitalWrite(LM1, HIGH);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
digitalWrite(LED, LOW);
delay(500);// bhai yaha se time change karke try kariyo perfet turn kitne time bad le rha h
// Stop();  // stop nhi kiya kyuki ghumke apne ap black strip detect karegi to rauk sakta hagar chahe



}

else if(digitalRead(LS) && digitalRead(RS) && digitalRead(ES)){
// Robot Home coming (Finish)
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
digitalWrite(LED, HIGH);
}
}
else
{
if(digitalRead(LS) && !digitalRead(RS)) // Turn left
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
Serial.println("Left");
digitalWrite(LED, LOW);

}
else if(!digitalRead(LS) && digitalRead(RS)) // turn right
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
Serial.println("Right");
digitalWrite(LED, LOW);

}
else if(!digitalRead(LS) && !digitalRead(RS)) // turn 180 degree
{
digitalWrite(LM1, HIGH);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, HIGH);
Serial.println("180");
digitalWrite(LED, LOW);

}
}
delay(5);
}

void Stop(){

digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
Serial.println("STOP");
digitalWrite(LED, LOW);
}


