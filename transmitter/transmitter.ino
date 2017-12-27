#include<Servo.h>
//SoftwareSerial mySerial(10, 11); // RX, TX

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536
#define M_PI 3.14159265359
#define dt 0.01

int ctrl1=4, ctrl2=5; // Control for MPUs 2 and 3

int valf1 = 0, valf2 = 0, valf3 = 0, valf4 = 0, valf5 = 0;
int angle1 = 0, angle2 = 0, angle3 = 0, angle4 = 0, angle5 = 0;
int prev=0, prevr=0, prevrise=0, prevrot=0;

MPU6050 IC1(0x68);
MPU6050 IC2(0x69);
MPU6050 IC3(0x69);

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
int16_t ax3, ay3, az3;
int16_t gx3, gy3, gz3;


bool blinkState = false;

int val1 = 0, val2 = 0, val3 = 0, val4 = 0;

void setup()
{ 
  Serial1.begin(38400);
  Wire.begin();
  Serial.begin(38400);

  IC1.initialize();
  IC2.initialize();
  IC3.initialize();
   
   
   pinMode(ctrl1,OUTPUT);
   pinMode(ctrl2,OUTPUT);
   
  Serial.println(IC1.testConnection() ? "MPU6050 #1 connection     successful" : "MPU6050 connection failed");
  Serial.println(IC2.testConnection() ? "MPU6050 #2 connection     successful" : "MPU6050 connection failed");
  Serial.println(IC3.testConnection() ? "MPU6050 #2 connection     successful" : "MPU6050 connection failed");
}


void loop()
{
  static float roll1;
  static float pitch1;
  int16_t accData1[3];
  int16_t gyrData1[3];

  static float roll2;
  static float pitch2;
  int16_t accData2[3];
  int16_t gyrData2[3];

  static float roll3;
  static float pitch3;
  int16_t accData3[3];
  int16_t gyrData3[3];
  //**********************************************MPU1*****************************************************
  digitalWrite(ctrl2,LOW);
  digitalWrite(ctrl1,LOW);
  
  IC1.getMotion6(&accData1[0], &accData1[1], &accData1[2], &gyrData1[0], &gyrData1[1], &gyrData1[2]);
  ComplementaryFilter1((short int*)accData1, (short int*)gyrData1, &pitch1, &roll1);
  val1 = map((int)pitch1, -5,30 , 0, 180);  
  val2 = map((int)roll1, -20,20 , 0, 180);
  //**********************************************MPU2*****************************************************
  
  digitalWrite(ctrl1,HIGH);
  IC2.getMotion6(&accData2[0], &accData2[1], &accData2[2], &gyrData2[0], &gyrData2[1], &gyrData2[2]);
  ComplementaryFilter2((short int*)accData2, (short int*)gyrData2, &pitch2, &roll2);
  val3 = map((int)roll2, -10,50 , 0, 180);
  digitalWrite(ctrl1,LOW);
  
  //**********************************************MPU3*****************************************************
 
  digitalWrite(ctrl2,HIGH);
  IC3.getMotion6(&accData3[0], &accData3[1], &accData3[2], &gyrData3[0], &gyrData3[1], &gyrData3[2]);
  ComplementaryFilter3((short int*)accData3, (short int*)gyrData3, &pitch3, &roll3);
  val4 = map((int)roll3, -15,80, 0, 180);
  digitalWrite(ctrl2,LOW);
  // val1=map(pitch1,-90,90,0,180);

  
  /*
  if(val1>=-5 && val1<=30)
    val1 = map(pitch1, -5,30 , 0, 180) ;
  if(val1>=-20 && val1<=20)
    val2 = map(roll1, -20,20 , 0, 180);
  if(val1>=-10 && val1<=50)
    val4 = map(roll2, -10,50 , 0, 180);
  if(val1>=-15 && val1<=80)
    val5 = map(roll3, -15,80, 0, 180);
*/


/*
**********************************************MAPPING MPUs*****************************************************
*    val1 = map((int)pitch1, -5,30 , 0, 180) ;
*  //if(val1>=-20 && val1<=20)
*    val2 = map((int)roll1, -20,20 , 0, 180);
*  //if(val1>=-10 && val1<=50)
*    val3 = map((int)roll2, -10,50 , 0, 180);
*  if(val1>=-15 && val1<=80)
*    val4 = map((int)roll3, -15,80, 0, 180);
*    
*/
//*************************************************************PRINTING********************************************************
 
  Serial.print("Wrist: ");
  Serial.print(pitch1);
  Serial.print("\t");
  Serial.print("Elbow: ");
  Serial.print(roll1);
  Serial.print("\t");
  Serial.print("Shoulder rise: ");
  Serial.print(roll2);
  Serial.print("\t");
  Serial.print("Shoulder rotate: ");
  Serial.print(roll3);
  Serial.print("\t\t");
  
//*********************************************PRINTING MAPPED VALUES*********************************************************
  Serial.print(val1);
  Serial.print("\t");
  Serial.print(val2);
  Serial.print("\t");
  Serial.print(val3);
  Serial.print("\t");
  Serial.print(val4);
  Serial.println("");

  
  //************************************************************SENDING MAPPED VALUES************************************************************************
  if (val1 > 0 && val1 < 180 && val2 > 0 && val2 < 180 && val3 > 0 && val3 < 180 && val4 > 0 && val4 < 180)
  {
    Serial1.write(201); Serial1.write(val1);
    Serial1.write(202); Serial1.write(val2);
    Serial1.write(203); Serial1.write(val3);
    Serial1.write(204); Serial1.write(val4);
  }



//*****************************************************************FINGERS**************************************************************************
//*****************************************************************FINGERS**************************************************************************
//*****************************************************************FINGERS**************************************************************************
//**************************************************************************************************************************************************  
    valf1=analogRead(A0);
    valf2=analogRead(A1);
    valf3=analogRead(A2);
    valf4=analogRead(A3);
    valf5=analogRead(A4);


/*
    angle1=map(valf1,413,358,10,170);
    angle2=map(valf2,413,358,10,170);
    angle3=map(valf3,413,358,10,170);
    angle4=map(valf4,413,358,10,170);
    angle5=map(valf5,413,358,10,170);
*/
//******************************************************************MAPPING FINGER VALUES*********************************************************
    angle1=map(valf1,358,480,170,10);
    angle2=map(valf2,358,480,170,10);
    angle3=map(valf3,358,480,170,10);
    angle4=map(valf4,358,480,170,10);
    angle5=map(valf5,358,480,170,10);
/*
 * 
//**********************************************************PRINTING MAPPED FINGER VALUES****************************************************
    Serial.print(valf1);Serial.print("\t");
    Serial.print(valf2);Serial.print("\t");
    Serial.print(valf3);Serial.print("\t");
    Serial.print(valf4);Serial.print("\t");
    Serial.print(valf5);Serial.print("\t");
    Serial.print(angle1);Serial.print("\t");
    Serial.print(angle2);Serial.print("\t");
    Serial.print(angle3);Serial.print("\t");
    Serial.print(angle4);Serial.print("\t");
    Serial.print(angle5);Serial.println("");
*/
 

    //********************************************************************SENDING MAPPED FINGER VALUES************************************************************************
    
    if(angle1>=10 && angle1<=170 && angle2>=10 && angle2<=170 && angle3>=10 && angle3<=170 && angle4>=10 && angle4<=170 && angle5>=10 && angle5<=170)
    {
    Serial1.write(205);Serial1.write(angle1);
    Serial1.write(206);Serial1.write(angle2);
    Serial1.write(207);Serial1.write(angle3);
    Serial1.write(208);Serial1.write(angle4);
    Serial1.write(209);Serial1.write(angle5);
    }
  delay(50);


}


//*****************************************************************************************************************************************************************************

void ComplementaryFilter1(short accData1[3], short gyrData1[3], float *pitch1, float *roll1)
{
  float pitchAcc1, rollAcc1;

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  *pitch1 += ((float)gyrData1[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
  *roll1 -= ((float)gyrData1[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis

  // Compensate for drift with accelerometer data if !bullshit
  // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
  int forceMagnitudeApprox = abs(accData1[0]) + abs(accData1[1]) + abs(accData1[2]);
  if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
  {
    // Turning around the X axis results in a vector on the Y-axis
    pitchAcc1 = atan2((float)accData1[1], (float)accData1[2]) * 180 / M_PI;
     if(*pitch1>prev)
      {
        *pitch1 = *pitch1 * 0.98 + pitchAcc1 * 0.02;
        prev=*pitch1;
      }
   else
   {
        *pitch1 = *pitch1 * 0.85 + pitchAcc1 * 0.02;
        prev=*pitch1;
    
   }
    
    // Turning around the Y axis results in a vector on the X-axis
    rollAcc1 = atan2((float)accData1[0], (float)accData1[2]) * 180 / M_PI;
    if(*pitch1>prevr)
    {
       *roll1 = *roll1 * 0.98 + rollAcc1 * 0.02;
       prevr=*roll1;
      }
      else if(*pitch1<prevr)
       {
       *roll1 = *roll1 * 0.85 + rollAcc1 * 0.02;
       prevr=*roll1;
      }
  }
  }

  
//*****************************************************************************************************************************************************************************

void ComplementaryFilter2(short accData2[3], short gyrData2[3], float *pitch2, float *roll2)
{
  float pitchAcc2, rollAcc2;

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  *pitch2 += ((float)gyrData2[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
  *roll2 -= ((float)gyrData2[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis

  // Compensate for drift with accelerometer data if !bullshit
  // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
  int forceMagnitudeApprox = abs(accData2[0]) + abs(accData2[1]) + abs(accData2[2]);
  if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
  {
// Turning around the Y axis results in a vector on the X-axis
   if(*roll2>prevrise)
   {
   rollAcc2 = atan2((float)accData2[0], (float)accData2[2]) * 180 / M_PI;
    *roll2 = *roll2 * 0.98 + rollAcc2 * 0.02;
  }
  else
  {
  rollAcc2 = atan2((float)accData2[0], (float)accData2[2]) * 180 / M_PI;
    *roll2 = *roll2 * 0.7 + rollAcc2 * 0.02;
    
  }
  }
}

//*****************************************************************************************************************************************************************************

void ComplementaryFilter3(short accData3[3], short gyrData3[3], float *pitch3, float *roll3)
{
  float pitchAcc3, rollAcc3;

  // Integrate the gyroscope data -> int(angularSpeed) = angle
  *pitch3 += ((float)gyrData3[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
  *roll3 -= ((float)gyrData3[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis

  // Compensate for drift with accelerometer data if !bullshit
  // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
  int forceMagnitudeApprox = abs(accData3[0]) + abs(accData3[1]) + abs(accData3[2]);
  if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
  {
    // Turning around the Y axis results in a vector on the X-axis
     if(*roll3>prevrot)
   {
     rollAcc3 = atan2((float)accData3[0], (float)accData3[2]) * 180 / M_PI;
    *roll3 = *roll3 * 0.98 + rollAcc3 * 0.02;
  }
  else
  {
     rollAcc3 = atan2((float)accData3[0], (float)accData3[2]) * 180 / M_PI;
    *roll3 = *roll3 * 0.7 + rollAcc3 * 0.02;
  }
  }
}
