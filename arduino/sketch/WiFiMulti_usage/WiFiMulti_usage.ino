/* Include required headers and/or libraries */
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

/* Instantiate a ESP8266WiFiMulti object called WiFiMulti */
ESP8266WiFiMulti WiFiMulti;

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Comment the following line to disable debug output */
  Serial.setDebugOutput(true);

  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Add your home/personal wifi here */
  WiFiMulti.addAP("personal-wifi", "the_password");

  /* If not found, will try to connect to this one */
  WiFiMulti.addAP("IoTesla",       "euroavia2019");
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Pass the control to WifiMulti so it can check the network */
  switch (WiFiMulti.run())
  {
    /* 'WiFiMulti.run()' returns a status code.
     * The following switch..case shows all the valid cases for didactic
     * purposes, but tipically is only checked one or two cases, if so.
     */

    case WL_IDLE_STATUS:
      Serial.printf("Returned WL_IDLE_STATUS\n");
      break;

    case WL_NO_SSID_AVAIL:
      Serial.printf("Returned WL_NO_SSID_AVAIL\n");
      break;

    case WL_SCAN_COMPLETED:
      Serial.printf("Returned WL_SCAN_COMPLETED\n");
      break;

    case WL_CONNECTED:
      Serial.printf("Returned WL_CONNECTED\n");
      break;

    case WL_CONNECT_FAILED:
      Serial.printf("Returned WL_CONNECT_FAILED\n");
      break;

    case WL_CONNECTION_LOST:
      Serial.printf("Returned WL_CONNECTION_LOST\n");
      break;

    case WL_DISCONNECTED:
      Serial.printf("Returned WL_DISCONNECTED\n");
      break;
  }

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
