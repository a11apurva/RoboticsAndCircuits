#include<Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536
#define M_PI 3.14159265359	    
#define dt 0.01	
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup()
{
    Wire.begin();
    Serial.begin(38400);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");  
}
void loop()
{
    static float roll;
    static float pitch;
    
    int16_t accData[3];
    int16_t gyrData[3];
    
 //   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        accelgyro.getMotion6(&accData[0], &accData[1], &accData[2], &gyrData[0], &gyrData[1], &gyrData[2]);
        ComplementaryFilter((short int*)accData, (short int*)gyrData, &pitch, &roll);
        Serial.print(accData[0]); Serial.print("\t");
        Serial.print(accData[1]); Serial.print("\t");
        Serial.print(accData[2]); Serial.print("\t");
        Serial.print(gyrData[0]); Serial.print("\t");
        Serial.print(gyrData[1]); Serial.print("\t");
        Serial.print(gyrData[2]); Serial.print("\t");
        Serial.print(pitch); Serial.print("\t");
        Serial.print(roll); Serial.print("\t");
}

void ComplementaryFilter(short accData[3], short gyrData[3], float *pitch, float *roll)
{
    float pitchAcc, rollAcc;               
 
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += ((float)gyrData[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    *roll -= ((float)gyrData[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis
 
    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(accData[0]) + abs(accData[1]) + abs(accData[2]);
    if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
    {
	// Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2((float)accData[1], (float)accData[2]) * 180 / M_PI;
        *pitch = *pitch * 0.98 + pitchAcc * 0.02;
 
	// Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2((float)accData[0], (float)accData[2]) * 180 / M_PI;
        *roll = *roll * 0.98 + rollAcc * 0.02;
    }
} 


