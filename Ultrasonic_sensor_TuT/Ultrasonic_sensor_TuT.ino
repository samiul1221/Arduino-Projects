int time;
int distance; 

void setup() {

  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(2,HIGH);
  delayMicroseconds(10);
  digitalWrite(2,LOW);
  
  
  delayMicroseconds(10);

  time = pulseIn(3,HIGH);

  distance = (0.0343*time)/2;
  Serial.print("The distance is : ");
  Serial.println(distance);
 
}
