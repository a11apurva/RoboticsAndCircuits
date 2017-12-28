#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536
#define M_PI 3.14159265359     
#define dt 0.01 

MPU6050 IC1(0x68);
MPU6050 IC2(0x69);

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
 
bool blinkState = false;

int val1=0,val2=0,val3=0,val4=0;

void setup()
 {
  Wire.begin();
  Serial.begin(38400);
  IC1.initialize();
  IC2.initialize();
   mySerial.begin(38400);
 
  Serial.println(IC1.testConnection() ? "MPU6050 #1 connection     successful" : "MPU6050 connection failed");
  Serial.println(IC2.testConnection() ? "MPU6050 #2 connection     successful" : "MPU6050 connection failed");
 
}
  void loop()
 {  static float roll1;
    static float pitch1;
    int16_t accData1[3];
    int16_t gyrData1[3];
    
    static float roll2;
    static float pitch2;
    int16_t accData2[3];
    int16_t gyrData2[3];
      
    
    IC1.getMotion6(&accData1[0], &accData1[1], &accData1[2], &gyrData1[0], &gyrData1[1], &gyrData1[2]);
    IC2.getMotion6(&accData2[0], &accData2[1], &accData2[2], &gyrData2[0], &gyrData2[1], &gyrData2[2]);
    ComplementaryFilter1((short int*)accData1, (short int*)gyrData1, &pitch1, &roll1);
    ComplementaryFilter2((short int*)accData2, (short int*)gyrData2, &pitch2, &roll2);

    val1=map(pitch1,-90,90,0,180);
    val2=map(roll1,-90,90,0,180);
    val3=map(pitch2,-90,90,0,180);
    val4=map(roll2,-90,90,0,180);

    
    Serial.print("MPU1:\t");
    Serial.print(accData1[0]);
    Serial.print("\t");
    Serial.print(accData1[1]);
    Serial.print("\t");
    Serial.print(accData1[2]);
    Serial.print("\t");
    Serial.print(gyrData1[0]);
    Serial.print("\t");
    Serial.print(gyrData1[1]);
    Serial.print("\t");
    Serial.print(gyrData1[2]);
    Serial.print("\t");
    Serial.print(pitch1); 
    Serial.print("\t");
    Serial.print(roll1); 
    Serial.print("\t");
    Serial.print(val1); 
    Serial.print("\t");
    Serial.print(val2); 
    Serial.println("\t");
   
   
    Serial.print("MPU2:\t");
    Serial.print(accData2[0]);
    Serial.print("\t");
    Serial.print(accData2[1]);
    Serial.print("\t");        
    Serial.print(accData2[2]);
    Serial.print("\t");
    Serial.print(gyrData2[0]);
    Serial.print("\t");
    Serial.print(gyrData2[1]);
    Serial.print("\t");
    Serial.print(gyrData2[2]); 
    Serial.print("\t");
    Serial.print(pitch2); 
    Serial.print("\t");
    Serial.print(roll2); 
    Serial.print("\t");
    Serial.print(val3); 
    Serial.print("\t");
    Serial.print(val4); 
    Serial.println("\t");
    

    
    if(val1>0 && val1<180 && val2>0 && val2<180 && val3>0 && val3<180 && val4>0 && val4<180)
      {
        mySerial.write(111); mySerial.write(val1); 
        mySerial.write(222); mySerial.write(val2); 
        mySerial.write(333); mySerial.write(val3); 
        mySerial.write(444); mySerial.write(val4); 
      }
    
   }
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
        *pitch1 = *pitch1 * 0.98 + pitchAcc1 * 0.02;
 
  // Turning around the Y axis results in a vector on the X-axis
        rollAcc1 = atan2((float)accData1[0], (float)accData1[2]) * 180 / M_PI;
        *roll1 = *roll1 * 0.98 + rollAcc1 * 0.02;
    }
} 
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
  // Turning around the X axis results in a vector on the Y-axis
        pitchAcc2 = atan2((float)accData2[1], (float)accData2[2]) * 180 / M_PI;
        *pitch2 = *pitch2 * 0.98 + pitchAcc2 * 0.02;
 
  // Turning around the Y axis results in a vector on the X-axis
        rollAcc2 = atan2((float)accData2[0], (float)accData2[2]) * 180 / M_PI;
        *roll2 = *roll2 * 0.98 + rollAcc2 * 0.02;
    }
}
