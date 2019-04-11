/* Include required headers and/or libraries */
#include <Wire.h>

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Join i2c bus (address optional for master) */
  Wire.begin(0, 2);

  /* start serial for output */
  Serial.begin(115200);
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Tell the BME280 where we want to read */
  Wire.beginTransmission(0x76);
  Wire.write(0xD0);
  Wire.endTransmission();

  /* Request data from slave with address 0x76 */
  Wire.requestFrom(0x76, 1);

  /* Wait for data to be available */
  while (Wire.available())
  {
    /* Receive the byte */
    uint8_t c = Wire.read();

    /* Send it to console/monitor */
    Serial.printf("Received byte: 0x%02X\n", c);
  }

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
