//http://www.youtube.com/user/greatscottlab
int ledred=8;
int ledgreen=9;
int ledblue=10;
int tx=1;
int rx=0;
char inSerial[15];


void setup(){
  Serial.begin(9600);
  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  allpinslow();
}

void loop(){
    int i=0;
    int m=0;
    delay(500);                                         
    if (Serial.available() > 0) {             
       while (Serial.available() > 0) {
         inSerial[i]=Serial.read(); 
         i++;      
       }
       inSerial[i]='\0';
      Check_Protocol(inSerial);
     }} 
     
void allpinslow()
{
digitalWrite(ledred, HIGH);
digitalWrite(ledgreen, HIGH);
digitalWrite(ledblue, HIGH);
}     
  
void Check_Protocol(char inStr[]){   
  int i=0;
  int m=0;
  Serial.println(inStr);
  
  if(!strcmp(inStr,"red")){      //Ledred ON
    allpinslow();
    digitalWrite(ledred, LOW);
    Serial.println("Red ON");
    for(m=0;m<11;m++){
      inStr[m]=0;}
       i=0;}
       
  if(!strcmp(inStr,"green")){      //Ledgreen ON
    allpinslow();
    digitalWrite(ledgreen, LOW);
    Serial.println("Green ON");
    for(m=0;m<11;m++){
      inStr[m]=0;}
       i=0;}
   
   if(!strcmp(inStr,"blue")){      //Ledblue ON
    allpinslow();
    digitalWrite(ledblue, LOW);
    Serial.println("Blue ON");
    for(m=0;m<11;m++){
      inStr[m]=0;}
       i=0;}
       
    else{
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;

}}
  
