/* Include required headers and/or libraries */
#include <ESP8266WiFi.h>

/* This block allows to be configured outside this code, but will use
 * the following information as default in case is not */
#if !defined(STASSID)
  #define STASSID "IoTesla"
  #define STAPSK  "euroavia2019"
#endif

/* Create wifi network information variables*/
const char    *ssid     = STASSID;
const char    *password = STAPSK;

/* Define the host and port to connect */
const char    *host     = "192.168.1.1";
const uint16_t port     = 80;

/* Data holder for received data */
#define RCV_DATA_MAX 1024
uint8_t rcv_data[RCV_DATA_MAX] = { 0x00 };

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Uncomment the following line to enable debug output */
  //Serial.setDebugOutput(true);

  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Report information about WiFi status */
  Serial.printf("Connecting to '%s' access point [", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  /* Wait until connected */
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf(".");
    delay(250);
  }                

  /* Ahoy! */
  Serial.printf("]\nConnected! Assigned IP: %s\n",
                WiFi.localIP().toString().c_str());
  /* Explaining the conversion shown over here:
   * 
   * localIP() returns a IPAddress class member
   *  - toString() returns a String class member
   *   - c_str() returns a C compliant string pointer
   */
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Now we're going to connect to a remote host using TCP */
  Serial.printf("Connecting to %s:%i ... ",
                host, port);

  /* To create a TCP connection we need the WiFiClient class */
  WiFiClient TCPClient;

  /* Try to connect */
  if (!TCPClient.connect(host, port))
  {
    Serial.printf("Failed!\nRetrying in 5 seconds ...\n");
    delay(5000);
    return;
  }
  Serial.printf("Done!\n");

  /* Send a request
   * As the remote host is a web server, use a compliant HTTP request
   */
  Serial.printf("Requesting /index.html\n");
  if (TCPClient.connected())
  {
    /* This is a common HTTP request (and uses \r\n instead of \n) */
    TCPClient.printf("GET /index.html HTTP/1.1\r\n"
                     "Host: %s\r\n"
                     "Accept: image/gif, image/jpeg, */*\r\n"
                     "Accept-Language: en-us\r\n"
                     "Accept-Encoding: gzip, deflate\r\n"
                     "User-Agent: IoTesla/1.0\r\n"
                     "\r\n"
                     "\r\n",
                     host);
  }

  /* Wait for the data to arrive
   * Attention must be paid to this type of wait block, as it don't use
   * simple delay to wait for incoming data. It waits "up to 5 seconds",
   * but will stop as soon as the data is ready.
   */
  /* Save current time in milliseconds */
  unsigned long timeout = millis();

  /* Wait until data is ready */
  while (TCPClient.available() == 0)
  {
    /* Not yet ready, we waited for more than 5 seconds? */
    if (millis() - timeout > 5000)
    {
      /* 5 seconds lapse is ended, reloop again after 10 seconds */
      Serial.printf("Connection timeout, no response\n");
      TCPClient.stop();
      delay(10000);
      return;
    }
  }

  /* Show the server response over the serial connection */
  Serial.printf("Response received:\n");

  /* Print data while still available (pay attention to %s format) */
  size_t rcv_bytes = 0;
  while (TCPClient.available())
  {
    while (rcv_bytes = TCPClient.read(rcv_data, RCV_DATA_MAX))
    {
      Serial.printf("Printing %i bytes ---\n%.*s\n---\n",
                    rcv_bytes,
                    rcv_bytes, rcv_data);
    }
  }

  /* Wrap-up and go! It's finished! */
  Serial.printf("Closing connection. Reloop in 10 seconds ...\n");
  TCPClient.stop();

  /* Ensure not to flood with a huge amount of fast data */
  delay(10000);
}
