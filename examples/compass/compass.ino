
#include "MPU9250.h"

MPU9250 IMU(i2c0, 0x68);
int status;

void setup()
{
  // serial to display data
  Serial.begin(9600);
  while (!Serial)
  {
  }
  // start communication with IMU
  status = IMU.begin();
  if (status < 0)
  {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1)
    {
    }
  }
  // setting the accelerometer full scale range to +/-8G
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_2G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_250DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_41HZ);
  // setting SRD to 19 for a 50 Hz update rate
  // IMU.setSrd(19);
  IMU.calibrateMag();
}

#define RAD_TO_DEG 57.295779513082320876798154814105

void loop()
{
  // read the sensor
  IMU.readSensor();

  // display the data Accel(%.6lf, %.6lf, %.6lf) Gyro(%.6lf, %.6lf, %.6lf) 
  // printf("\r\n Mag(%.6f, %.6f, %.6f) Yaw %.6f ", 
  //   // IMU.getAccelX_mss(), IMU.getAccelX_mss(), IMU.getAccelY_mss(), IMU.getAccelZ_mss(), IMU.getGyroX_rads(), IMU.getGyroY_rads(), IMU.getGyroZ_rads(), 
  //   IMU.getMagX_uT(), IMU.getMagY_uT(), IMU.getMagZ_uT(), float(atan2(IMU.getMagY_uT(), IMU.getMagX_uT())) * RAD_TO_DEG
  // );
  Serial.printf("\r\n Yaw %.6f ", 
    float(atan2(IMU.getMagY_uT(), IMU.getMagX_uT())) * RAD_TO_DEG
  );
  delay(20);
}
