int mono = 6;         //PWM pin mono strip is on
int monoSwitch = 7;   //pin switch on
int switchState = 0;  // switch state starts at 0/off

void setup() {
  Serial.begin(9600);
  //open serial port at 9600 baud rate
  pinMode(monoSwitch, INPUT);
  //set switch pin as input
}

voice loop() {
  if (switchState == 1) {

    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // fade IN from min to max in increments of 5
      analogWrite(mono, fadeValue);
      //write fadeValue (values 0 - 255) to PWM pin strip is on
      delay(50);
      //wait for 50 milliseconds to see the dimming effect
    }


    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      // fade out from max to min in increments of 5

      analogWrite(mono, fadeValue);
      //write fadeValue (values 0 - 255) to PWM pin strip is on

      delay(50);
      // wait for 50 milliseconds to see the dimming effect
    }
  }
  Serial.println (switchState);
  //print switchState to serial window to see on/off values (1/0)
}
