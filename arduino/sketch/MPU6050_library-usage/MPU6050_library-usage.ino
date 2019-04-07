/* Include required headers and/or libraries */
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define MPU6050_ADDRESS 0x68

/* Instantiate a MPU6050 object called MPU6050_obj */
MPU6050 MPU6050_obj(MPU6050_ADDRESS);

/* Used to translate from digital to human */
struct meas_range
{
  uint16_t ranges[4];
  uint8_t current;
}
MPU6050_range[2] =
{
  { .ranges = { 250, 500, 1000, 2000 }, .current = 0 },
  { .ranges = { 2, 4, 8, 16 },          .current = 0 },
};
#define RANGE_GYRO  0
#define RANGE_ACCEL 1

/* Get a gyro or accel raw value and convert to human-readable */
float raw_to_human(struct meas_range *range, int16_t raw_val)
{
  /* Uncomment to get details about conversion */
  //printf("Converting 0x%04X\n"
  //       " - %s range, current %u, value %u\n"
  //       " - Converted value %2.2f\n",
  //       raw_val,
  //       (range == &MPU6050_range[0])?" Gyro":"Accel",
  //       range->current, range->ranges[range->current],
  //       (((float)raw_val * range->ranges[range->current]) / 0x7FFF)
  //       );
  return (((float)raw_val * range->ranges[range->current]) / 0x7FFF);
}

/* Convert a temperature value, method differs from gyro/accel */
float temp_to_human(int16_t raw_val)
{
  return (((float)raw_val / 340) + 36.53);
}

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Join I2C bus and set it to 400 kHz */
  Wire.begin();
  Wire.setClock(400000);

  /* Initialize the sensor */
  MPU6050_obj.initialize();

  /* Check communication before continue */
  if (MPU6050_obj.testConnection() == false)
  {
    Serial.printf("The sensor did not respond. Please check wiring.\n");
    
    /* Stop here (WDT will reset at some point) */
    while(1);
  }

  /* By default, the library uses the following settings:
   * - setFullScaleGyroRange(MPU6050_GYRO_FS_250)
   * - setFullScaleAccelRange(MPU6050_ACCEL_FS_2)
   */

  /* Configure Gyroscope range, choose from:
   * - MPU6050_GYRO_FS_250 ..: +/-250 deg/sec
   * - MPU6050_GYRO_FS_500 ..: +/-500 deg/sec
   * - MPU6050_GYRO_FS_1000 .: +/-1000 deg/sec
   * - MPU6050_GYRO_FS_2000 .: +/-2000 deg/sec
   *
   * Uncomment the following two lines to set a different value
   */
  //MPU6050_range[RANGE_GYRO].current = MPU6050_GYRO_FS_2000;
  //MPU6050_obj.setFullScaleGyroRange(MPU6050_range[RANGE_GYRO].current);

  /* Configure Accelerometer range, choose from:
   * - MPU6050_ACCEL_FS_2 ...: +/-2g
   * - MPU6050_ACCEL_FS_4 ...: +/-4g
   * - MPU6050_ACCEL_FS_8 ...: +/-8g
   * - MPU6050_ACCEL_FS_16 ..: +/-16g
   *
   * Uncomment the following two lines to set a different value
   */
  //MPU6050_range[RANGE_ACCEL].current = MPU6050_ACCEL_FS_16;
  //MPU6050_obj.setFullScaleAccelRange(MPU6050_range[RANGE_ACCEL].current);
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Read and print sensor data */
  Serial.printf(" - Temperature ....: %2.2f [degC]\n",
                temp_to_human(MPU6050_obj.getTemperature()));
  Serial.printf(" - Rotation X .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             MPU6050_obj.getRotationX()));
  Serial.printf(" - Rotation Y .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             MPU6050_obj.getRotationY()));
  Serial.printf(" - Rotation Z .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             MPU6050_obj.getRotationZ()));
  Serial.printf(" - Acceleration X .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             MPU6050_obj.getAccelerationX()));
  Serial.printf(" - Acceleration Y .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             MPU6050_obj.getAccelerationY()));
  Serial.printf(" - Acceleration Z .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             MPU6050_obj.getAccelerationZ()));

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}