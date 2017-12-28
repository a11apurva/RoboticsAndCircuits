//#include "Ultrasonic.h"
#include <Servo.h>

#define k 30
String data="";
int len=0; 
int turn=400;
int enableLeft = 11, enableRight = 8, leftMotorFront = 13, leftMotorBack = 12, rightMotorFront = 9, rightMotorBack = 10;

//Define pins ultrasonic(trig,echo)
//Ultrasonic ultrasonic(A0,A1);
//Variables
int distance;
int pos1 = 0;
int pos2 = 0;
Servo myservo1,myservo2,myservo3;  // create servo object to control a servo



void front(){
  digitalWrite(leftMotorFront,HIGH); 
  digitalWrite(leftMotorBack,LOW);
  digitalWrite(rightMotorFront,HIGH);
  digitalWrite(rightMotorBack,LOW);
  Serial.println("Front ");  
}


void back(){
  digitalWrite(leftMotorFront,LOW);
  digitalWrite(leftMotorBack,HIGH);
  digitalWrite(rightMotorFront,LOW);
  digitalWrite(rightMotorBack,HIGH);
  Serial.println("Back ");
}

void left(){
  digitalWrite(leftMotorFront,LOW);
  digitalWrite(leftMotorBack,HIGH);
  digitalWrite(rightMotorFront,HIGH); 
  digitalWrite(rightMotorBack,LOW);
  Serial.println("Left ");
}

void right(){
  digitalWrite(leftMotorFront,HIGH);
  digitalWrite(leftMotorBack,LOW);
  digitalWrite(rightMotorFront,LOW);
  digitalWrite(rightMotorBack,HIGH);
  Serial.println("Right ");
}


void botStop(){
  digitalWrite(leftMotorFront,LOW);
  digitalWrite(leftMotorBack,LOW);
  digitalWrite(rightMotorFront,LOW);
  digitalWrite(rightMotorBack,LOW);
  Serial.println("Stop ");
}

void Gup()
{
    for (int pos=180; pos >= 90; pos -= 1){
    myservo3.write(pos);             
    delay(15);                      
    }  
}
void Grab()
{
   for (; pos1 <= 175; pos1 += 1,pos2-=1){
    myservo1.write(pos1);             
    myservo2.write(pos2);             
    delay(15);                      
    }
}
void Gopen()
{
     for (pos1 = 175, pos2=0 ; pos1 >= 80; pos1 -= 1,pos2+=1) { 
    myservo1.write(pos1);             
    myservo2.write(pos2);             
    delay(15);                      
    }

}
void Gdown()
{
    for (int pos=90; pos <= 180; pos += 1){
    myservo3.write(pos);             
    delay(15);                      
    }
  
}

void turnAround()
{
    left();
    delay(2*turn);  //turn 180
    botStop();  
}  

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  pinMode(leftMotorFront,OUTPUT);
  pinMode(leftMotorBack,OUTPUT);
  pinMode(rightMotorFront,OUTPUT);
  pinMode(rightMotorBack,OUTPUT);
  pinMode(enableLeft,OUTPUT);
  pinMode(enableRight,OUTPUT);
 
  digitalWrite(enableLeft,1);
  digitalWrite(enableRight,1);

  pinMode(13,OUTPUT);

  //set servos for gripper
  myservo1.attach(3);  // left servo  9
  myservo2.attach(5);  //right s   10
  myservo3.attach(6);  // center    11
  myservo1.write(175);
  myservo2.write(5);

}
void loop()
{
  while (Serial.available() == 0); 
 // read the incoming byte:
   int data = Serial.read();
//   int dir=data.toInt();
   
    switch(data)
{     
     case 'S':
     botStop();
  
     break;
     case 'F':
     front();
     delay(k);
     botStop();
  
     break;
     case 'R':
     right();
     delay(k);
     botStop();
  
     break;
     case 'L':
     left();
     delay(k);
     botStop();
     break;

     case 'B':
     back();
     delay(k);
     botStop();
     break;
     
     default:
     Serial.println("Other Cases ");
    // otherCases(data);
}

}

//void otherCases(String data)
//{
//  if(data=="Clean")
//  {
//      distance = ultrasonic.Ranging(CM);
//
//    if(distance<20&&distance!=0)
//  {  
//    Serial.print("*FOUND*\t");
//    turnAround();
//    Gopen();
//    delay(350);
//    //gripper down
//    Gdown();
//// move a little front
//    front();
//    delay(350);
//    botStop();
//   //pick it up 
//    Grab();
//    delay(350);
//    Gup();
//    delay(350);
//  }
//   if(distance==0)       // if sensor misbehaves
//   {
//      pinMode(A1,OUTPUT);
//      delay(30);
//      pinMode(A1,INPUT);
//   }
// // Serial.print("Object found at: ");
//  Serial.print(distance);
//  Serial.println("cm");
//  delay(250);
//  if(distance>20)
//  {
//    //*************Vaccum Cleaning**********
//  }
//  }
//}
