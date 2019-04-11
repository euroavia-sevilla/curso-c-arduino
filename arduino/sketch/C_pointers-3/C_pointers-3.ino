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

/* Let's define a data model for easy printing */
struct print_model
{
  char first_column[16];
  char cell_format[16];
  size_t cell_size;
  void *row_pt;
};

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Create a few arrays */
  uint8_t  arr_u8[8] = {  1,   2,   3,   4,   5,   6,   7,   8  };
  int8_t   arr_i8[8] = { -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8  };
  char     arr_ch[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

  /* Let's define each row element to be shown */
  struct print_model our_table[5] =
  {
    { " Type    ", "| Index nr.%u ", 0,               NULL   },
    { "---------", "+------------",  0,               NULL   },
    { " uint8_t ", "| 0x%08X ",      sizeof(uint8_t), arr_u8 },
    { "  int8_t ", "| 0x%08X ",      sizeof(int8_t),  arr_i8 },
    { "    char ", "| 0x%08X ",      sizeof(char),    arr_ch }
  };

  /* 
   * Print a table of addresses
   */

  /* Helper variables */
  uint8_t col = 0;
  uint8_t row = 0;
  Serial.printf("Address of each array member:\n");
  Serial.printf("\n");

  for (row = 0; row < 5; row++)
  {
    for (col = 0; col < 8; col++)
    {
      if (our_table[row].cell_size == 0)
      {
        /* Header and separator: size = 0 */
        Serial.printf(our_table[row].cell_format, col);
      }
      else
      {
        /* Non-headers: size > 0 */
        Serial.printf(our_table[row].cell_format,
                      (uint8_t *)our_table[row].row_pt
                              + (our_table[row].cell_size * col)
                      );
      }
    }
    Serial.printf("\n");
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
