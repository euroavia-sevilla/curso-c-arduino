/* Include required headers and/or libraries */
#include <FS.h>

#define TESTFILE "/test_file.txt"

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Initialize the file system */
  Serial.printf("Initializing SPIFFS\n");
  if (SPIFFS.begin() == false)
  {
    Serial.printf("SPIFFS cannot be initialized\n");
    
    /* Stop here (WDT will reset at some point) */
    while(1) {};
  }
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  File test_file;
  #define MY_STR_LEN 1024
  uint8_t my_string[MY_STR_LEN];
  uint16_t my_line = 0;

  /* The file already exist? */
  if (SPIFFS.exists(TESTFILE))
  {
    Serial.printf("File '" TESTFILE "'' IS found'\n");
  }
  else
  {
    Serial.printf("File '" TESTFILE "'' NOT found'\n");
  }

  /* Mode 'a+' create if not exists:
   *  - Read from the beginning of the file
   *  - Append new data at the end
   *  * Useful for buffers ;)
   */
  test_file = SPIFFS.open(TESTFILE, "a+");
  if (!test_file)
  {
    /* Oh man, this is serious */
    Serial.printf("Cannot open '" TESTFILE "'' for appending'\n");
  }
  else
  {
    Serial.printf("Opened '" TESTFILE "'\n");

    /* Opened, now put some (at the end of the file) */
    Serial.printf("Filling file '" TESTFILE "' with some data\n");
    test_file.printf("This is the first line\n");
    test_file.printf("This is the second line\n");
    test_file.printf("This is the third line\n");
    test_file.close();

    /* Mode 'r' create if not exists:
     *  - Read from the beginning of the file
     *  - Fails if file not exists
     *  * Useful for safe readings without data modification
     */
    test_file = SPIFFS.open(TESTFILE, "r");
    Serial.printf("Reopened '" TESTFILE "' for reading\n");
    Serial.printf("Contents of file '" TESTFILE "'\n");
    my_line = 0;
    while (test_file.position() < test_file.size())
    {
      test_file.readBytesUntil('\n', my_string, MY_STR_LEN);
      Serial.printf("Line %03d: %s\n", my_line++, my_string);
    }

    /* Done, free/close the file */
    test_file.close();
    Serial.printf("Closed '" TESTFILE "'\n");

    /* Remove the file */
    SPIFFS.remove(TESTFILE);
    Serial.printf("Removed '" TESTFILE "'\n");
  }

  /* Process is locked until reset is performed */
  Serial.printf("Locking now\n");
  while (true)
  {
    /* Ensure other tasks are working (avoid WDT reset) */
    yield();
  }
}
