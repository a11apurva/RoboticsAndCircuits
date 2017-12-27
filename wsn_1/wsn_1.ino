#include<SoftwareSerial.h>

SoftwareSerial esp(2,3);

#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char   buffer[48];



void setup() {
  // put your setup code here, to run once:
  esp.begin(9600);
  Serial.begin(9600);
  dht.begin();

  delay(4000);  

  esp.println("AT");
  delay(4000);
  while(esp.available())
    Serial.write(esp.read());
  
  /*
  esp.println("AT+CWMODE=1");
  delay(4000);
  while(esp.available())
    Serial.write(esp.read());
  
  esp.println("AT+CWJAP=\"123\",\"87654321\"");
  delay(10000);
  while(esp.available())
    Serial.write(esp.read());
    */
  
  esp.println("AT+CIPMUX=0");
  delay(4000);
  while(esp.available())
    Serial.write(esp.read());

   Serial.write("************");
    
}

void loop() {
 
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  String cmd1="GET /update?api_key=3IVMQ2A6ZW09CINT&field1=";

  cmd1.concat(h);
  cmd1.concat("&field2=");
  cmd1.concat(t);

  
  esp.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
  delay(500);
   
  while(esp.available())
    Serial.write(esp.read());
  
  esp.println("AT+CIPSEND=58");
  delay(500);
  
  while(esp.available())
    Serial.write(esp.read());
    
  esp.println(cmd1);
  Serial.println(cmd1);
  delay(500);

  while(esp.available())
    Serial.write(esp.read());


  Serial.write("************");

}
