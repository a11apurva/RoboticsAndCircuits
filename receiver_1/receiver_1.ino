#include <Servo.h>

Servo Servo1;  // create servo object to control a servo
Servo Servo2;  // create servo object to control a servo
Servo Servo3;  // create servo object to control a servo

void setup()
{
  Serial1.begin(38400);
  Serial.begin(38400);
  Servo1.attach(6);
  Servo2.attach(7);
  Servo3.attach(8); 
  
  Servo1.write(5);
  Servo2.write(5);
  Servo3.write(5);
  delay(1000); 
}

int flag=1;int n=0;
int val=0;

void loop()
{
  if(Serial1.available()>0)
  {
    
    flag=Serial1.read();
    Serial.println(flag);
   
    if(flag==201)
    {
      Serial.print("hello 1");
      if(Serial1.available()>0)
      {
        //Serial.print("helloxxxxxxxxxxxx");
        n=Serial1.read();
        Serial.print("  MPU_1.1: ") ;
        Serial.print(n);
        Servo1.write(n);
      }
    }
    else if(flag==202)
    {
      //Serial.print("hello 2");
      if(Serial1.available()>0)
      {
        n=Serial1.read();
        Serial.print("\tMPU_1.2: ") ;
        Serial.print(n);
        Servo2.write(n);
      }
    }
    else if(flag==203)
    {
      //Serial.print("hello 3");
      if(Serial1.available()>0)
      {
        n=Serial1.read();
        Serial.print(" \tMPU_2.1: ") ;
        Serial.print(n);
        Servo3.write(n);
      }
    }
    else if(flag==204)
    {
      //Serial.print("hello 4");
      if(Serial1.available()>0)
      {
        n=Serial1.read();
        Serial.print("\tMPU_2.2: ") ;
        Serial.println(n);
        Stepper1(n);
      }
    }
  }
}

void Stepper1(int n)
{}
