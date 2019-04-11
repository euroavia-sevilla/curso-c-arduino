/* Include required headers and/or libraries */

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Create a few arrays */
  uint8_t  arr_u8[8] = {  1,   2,   3,   4,   5,   6,   7,   8  };
  int8_t   arr_i8[8] = { -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8  };
  char     arr_ch[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

  /* 
   * Print a table of addresses
   */

  /* Helper variables */
  uint8_t idx0       = 0;
  Serial.printf("Address of each array member:\n");
  Serial.printf("\n");

  /* Table: Header */
  Serial.printf(" Type    ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| Index nr.%u ", idx0);
  }
  Serial.printf("\n");

  /* Table: Separator */
  Serial.printf("---------");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("+------------");
  }
  Serial.printf("\n");

  /* Table: uint8_t row */
  Serial.printf(" uint8_t ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_u8[idx0]);
  }
  Serial.printf("\n");
  
  /* Table: int8_t row */
  Serial.printf("  int8_t ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_i8[idx0]);
  }
  Serial.printf("\n");
  
  /* Table: char row */
  Serial.printf("    char ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_ch[idx0]);
  }
  Serial.printf("\n");

  /* Create a few simple (single) pointers */
  uint8_t  *pt_u8    = &arr_u8[7];
  int8_t   *pt_i8    = &arr_i8[7];
  char     *pt_ch    = &arr_ch[7];
  uint32_t *pt_u32   = NULL;

  /* Check some variables assignments */
  Serial.printf("\n");
  Serial.printf("Checking variables assignments:\n");
  Serial.printf(" - Indirect-access (using pointers):\n");
  Serial.printf("   - Pointed by pt_u8 ..: %8u [0x%08X]\n", *pt_u8, *pt_u8);
  Serial.printf("   - Pointed by pt_i8 ..: %8i [0x%08X]\n", *pt_i8, *pt_i8);
  Serial.printf("   - Pointed by pt_ch ..: %8c [0x%08X]\n", *pt_ch, *pt_ch);

  /* What if we re-read an address thinking it has a different sign? */
  pt_u8 = (uint8_t *)pt_i8;
  Serial.printf(" - A uint8_t reading data from a negative int8_t:\n");
  Serial.printf("   - Pointed by pt_u8 ..: %8u [0x%08X]\n", *pt_u8, *pt_u8);

  /* What if we re-read it again, but thinking on different size? */
  pt_u32 = (uint32_t *)pt_i8;
  Serial.printf(" - A uint32_t reading data from a negative int8_t:\n");
  Serial.printf("   - Pointed by pt_u32 .: %8u [0x%08X]\n", *pt_u32, *pt_u32);

  /* ~~ o ~~ */

  /* Process is locked until reset is performed */
  Serial.printf("Locking now\n");
  while (true)
  {
    /* Ensure other tasks are working (avoid WDT reset) */
    yield();
  }
}
