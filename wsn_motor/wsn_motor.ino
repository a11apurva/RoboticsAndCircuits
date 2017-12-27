void setup() {
 Serial.begin(9600);
 pinMode(12,OUTPUT);
 pinMode(13,OUTPUT);
 digitalWrite(12,LOW); // forwards pin
 digitalWrite(13,LOW); //  backward pin
}
int n;
int threshold=53;
void loop() {
 
  if(Serial.available()>0)
  {
    n=Serial.read();
    Serial.write(n);
    if (n>threshold)
    {
      digitalWrite(12,HIGH);
      Serial.write(n);
      Serial.write("OK");
    }

    delay(2000);
    
    digitalWrite(12,LOW);    
  
   }
  


}

