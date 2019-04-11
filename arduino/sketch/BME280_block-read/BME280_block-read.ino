/* Include required headers and/or libraries */
#include <Wire.h>

#define SLAVE_ADDRESS 0x76
#define BLOCK_ADDRESS 0x88
#define BLOCK_LENGTH 118

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Join i2c bus (address optional for master) */
  Wire.begin();

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
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(BLOCK_ADDRESS);
  Wire.endTransmission();

  /* Use static to prevent block re-allocation on each pass */
  static uint8_t memory_map[BLOCK_LENGTH] = { 0x00 };

  /* Array index, stores position to write a received byte */
  uint8_t memory_idx = 0;

  /* Used to check the received amount */
  uint8_t rx_bytes = 0;

  /* Request data from slave */
  Wire.requestFrom(SLAVE_ADDRESS, BLOCK_LENGTH);

  /* Wait for data to be available */
  while (rx_bytes == 0)
  {
    rx_bytes = Wire.available();
  }

  /* Save the block */
  for (memory_idx = 0; memory_idx < rx_bytes; memory_idx++)
  {
    memory_map[memory_idx] = Wire.read();
  }

  /* Print the block */
  Serial.printf(" ++ | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
  Serial.printf("----+------------------------------------------------");
  for (memory_idx = 0; memory_idx < rx_bytes; memory_idx++)
  {
    /* Create a new line each 16 printed bytes */
    if ((memory_idx % 16) == 0)
    {
      Serial.printf("\n %02X |", memory_idx + BLOCK_ADDRESS);
    }

    /* Print a byte */
    Serial.printf(" %02X", memory_map[memory_idx]);
  }
  Serial.printf("\nEnd of data\n");

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
