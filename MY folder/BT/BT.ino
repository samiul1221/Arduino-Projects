void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    int val = Serial.read();
    if(val==49){
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    }
    if(val==50){
    digitalWrite(8,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(11,LOW);


    }
    if(val==52){
    Serial.println("RIGHT");
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    }
    if(val==51){
    Serial.println("LEFT");
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(8,LOW);
    }
  }
}
