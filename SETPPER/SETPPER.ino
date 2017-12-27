const int stepd=3, directiond=4;

void setup() {
  // put your setup code here, to run once:
pinMode(stepd,OUTPUT);
pinMode(directiond,OUTPUT);
}

void loop() {
  digitalWrite(directiond,HIGH);
  for(int i=0;i<200;i++)
  {
  digitalWrite(stepd,HIGH);
    delayMicroseconds(500);
    
  digitalWrite(stepd,LOW);
    delayMicroseconds(500);
}
delay(1000);
  digitalWrite(directiond,LOW);

  for(int i=0;i<200;i++)
  {
  digitalWrite(stepd,HIGH);
    delayMicroseconds(500);
    
  digitalWrite(stepd,LOW);
    delayMicroseconds(500);
}
delay(1000);}
