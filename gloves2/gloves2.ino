#include<Servo.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

Servo s1,s2,s3,s4,s5;

void setup() {
  s1.attach(6);
  s2.attach(7);
  s3.attach(8);
  s4.attach(9);
  s5.attach(10);

  /*
  s1.write(5);
  s2.write(5);
  s3.write(5);
  s4.write(5);
  s5.write(5);
  */
  mySerial.begin(9600);
  Serial.begin(9600);
}


int valf1, valf2,valf3,valf4,valf5,angle1,angle2,angle3,angle4,angle5;

void loop() {

    valf1=analogRead(A0);
    valf2=analogRead(A1);
    valf3=analogRead(A2);
    valf4=analogRead(A3);
    valf5=analogRead(A4);

    angle1=map(valf1,320,470,170,10);//420
    angle2=map(valf2,320,470,170,10);
    angle3=map(valf3,320,470,170,10);//450
    angle4=map(valf4,320,470,170,10);//350//485
    angle5=map(valf5,350,470,170,10);//320//485

     
     
     
     Serial.print(valf1);
     Serial.print("\t");
     Serial.print(valf2);
     Serial.print("\t");
     Serial.print(valf3);
     Serial.print("\t");
     Serial.print(valf4);
     Serial.print("\t");
     Serial.print(valf5);
     Serial.print("\t***\t");
     Serial.print(angle1);
     Serial.print("\t");
     Serial.print(angle2);
     Serial.print("\t");
     Serial.print(angle3);
     Serial.print("\t");
     Serial.print(angle4);
     Serial.print("\t");
     Serial.print(angle5);
     Serial.print("\t***\t");





     if(angle1<60)
        angle1=5;
     else if(angle1>=60 && angle1<120)
        angle1=90;
     else if(angle1>=120 )
        angle1=175;

     if(angle2<60)
        angle2=5;
     else if(angle2>=60 && angle2<120)
        angle2=90;
     else if(angle2>=120)
        angle2=175;

     if(angle3<60)
        angle3=5;
     else if(angle3>=60 && angle3<120)
        angle3=90;
     else if(angle3>=120)
        angle3=175;

     if(angle4<60)
        angle4=5;
     else if(angle4>=60 && angle4<120)
        angle4=90;
     else if(angle4>=120)
        angle4=175;

     if(angle5<60)
        angle5=5;
     else if(angle5>=60 && angle5<120)
        angle5=90;
     else if(angle5>=120)
        angle5=175;


     Serial.print(angle1);
     Serial.print("\t");
     Serial.print(angle2);
     Serial.print("\t");
     Serial.print(angle3);
     Serial.print("\t");
     Serial.print(angle4);
     Serial.print("\t");
     Serial.print(angle5);
     Serial.println("");
     
      if(angle1>=0 && angle1<=175 && angle2>=0 && angle2<=175 && angle3>=0 && angle3<=175 && angle4>=0 && angle4<=175 && angle5>=0 && angle5<=175 )
      {
        /*
     s1.write(angle1);
     s2.write(angle2);
     s3.write(angle3);
     s4.write(angle4);
     s5.write(angle5);
     */
        mySerial.write(205); mySerial.write(angle1);
        mySerial.write(206); mySerial.write(angle2);
        mySerial.write(207); mySerial.write(angle3);
        mySerial.write(208); mySerial.write(angle4);
        mySerial.write(209); mySerial.write(angle5);
      }
     delay(500);
}
