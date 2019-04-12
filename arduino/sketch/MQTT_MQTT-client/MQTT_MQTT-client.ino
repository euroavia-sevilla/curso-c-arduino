/* Include required headers and/or libraries */
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
/* https://github.com/256dpi/arduino-mqtt */
#include <MQTT.h>

/* This allows 'ESP.getVcc()' to be used */
ADC_MODE(ADC_VCC);

/* This block allows to be configured outside this code, but will use
 * the following information as default in case is not */
#if !defined(STASSID)
  #define STASSID "IoTesla"
  #define STAPSK  "euroavia2019"
#endif

/* Define the MQTT host and port to connect to */
const char    *mqtt_host     = "192.168.1.1";
const uint16_t mqtt_port     = 1883;
const char    *mqtt_user     = "tc_d1_0000";
const char    *mqtt_pass     = "euroavia2019";

/* Defined topics for IoTesla */
const char *topic_list[3] =
{
  /* euroavia-pool/# */
  "euroavia-pool/#",
  /* euroavia-pool/USERNAME/# */
  "euroavia-pool/%s/%s",
  /* euroavia-devices/USERNAME/# */
  "euroavia-devices/%s/%s"
};
#define PUBLIC_SUSCRIBE 0
#define PUBLIC_PUBLISH  1
#define PRIVATE_USAGE   2

/* Instantiate the required objects */
ESP8266WiFiMulti WiFiMulti;
WiFiClient espClient;
MQTTClient mqttClient;

/* Data holder send/receive data */
#define BUF_DATA_MAX 1024
char buf_data[BUF_DATA_MAX] = { 0x00 };

/* Used to count the time */
unsigned long millis_now = 0;
unsigned long millis_last = 0;

/* A basic sensor data structure */
struct sensor_data
{
  float temperature;
  float humidity;
  float pressure;
  float altitude;
  float supply_vcc;
};

/* Create a variable to hold the sensor data */
struct sensor_data sdata;

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n"
                "---\n"
                "> Testing: 256dpi's MQTT.h library\n"
                "---\n"
                );

  /* Ensure to work as Station (disables internal AP) */
  WiFi.mode(WIFI_STA);

  /* Add your home/personal wifi here */
  WiFiMulti.addAP("personal-wifi", "the_password");

  /* If not found, will try to connect to this one */
  WiFiMulti.addAP("IoTesla",       "euroavia2019");
  mqttClient.begin(mqtt_host, mqtt_port, espClient);
}

/*
 * This function will fill a structure with sensor data
 * For this example, is just fake data
 * - Returns 0 if OK. Non 0 for error or warning
 */
int get_sensor_data(struct sensor_data *sdata)
{
  sdata->temperature = ( 2000.0 + random(1000))/100;
  sdata->humidity    = ( 4000.0 + random(2000))/100;
  sdata->pressure    = (10000.0 + random(5000))/100;
  sdata->altitude    = (20000.0 + random(10000))/100;
  sdata->supply_vcc  = 1.0 * ESP.getVcc();
  return 0;
}

/*
 * This function takes a structure with sensor data and upload
 * it to MQTT broker
 * - Returns 0 if OK. Non 0 for error or warning
 */
int upload_sensor_data(struct sensor_data *sdata)
{
  static int res;

  /* Compose a JSON string with sensor data */
  snprintf(buf_data, BUF_DATA_MAX,
           "{"
           " tmp: %.2f,"
           " hum: %.2f,"
           " prs: %.2f,"
           " alt: %.2f,"
           " vcc: %.2f "
           "}",
           sdata->temperature,
           sdata->humidity,
           sdata->pressure,
           sdata->altitude,
           sdata->supply_vcc
           );
  res = mqttClient.publish(get_topic_name(PUBLIC_PUBLISH, "sensors"), buf_data);
  Serial.printf("Sensor data published ... %s\n", (res)?"OK":"FAIL");

  /* Opposite interface here, 1 for OK is translated to 0 for OK */
  return res?0:1;
}

/*
 * Build a topic string and return a pointer to it
 */
char *get_topic_name(uint8_t topic_id, char *endpoint)
{
  /* Topic name holder */
  #define TOPIC_NAME_MAX 256
  static char topic_name[TOPIC_NAME_MAX] = { 0x00 };

  /* Select topic specifics */
  switch (topic_id)
  {
    /* No variable sustitution needed */
    case PUBLIC_SUSCRIBE:
      snprintf(topic_name, TOPIC_NAME_MAX, topic_list[topic_id]);
      break;

    /* Need 2 variable sustitutitons */
    case PUBLIC_PUBLISH:
    case PRIVATE_USAGE:
      snprintf(topic_name, TOPIC_NAME_MAX, topic_list[topic_id],
               mqtt_user, endpoint);
      break;

    /* Dunno what ur saying */
    default:
      /* Set an empty string as result */
      topic_name[0] = 0x00;
      break;
  }

  /* Let's go! */
  return topic_name;
}

/*
 * This function is used to make a new connection to MQTT broker
 */
void mqtt_connect()
{
  /* Non-stop retries */
  while (!mqttClient.connected())
  {
    /* Use the board+flash IDs as identifier */
    snprintf(buf_data, BUF_DATA_MAX,
             "IoTesla-%08X-%08X\n",
             ESP.getChipId(), ESP.getFlashChipId());

    /* Connect to broker */
    Serial.printf("Connecting to MQTT broker:\n"
                  " - username ..: %s\n"
                  " - client ID .: %s\n",
                  mqtt_user, buf_data);
    if (mqttClient.connect(buf_data, mqtt_user, mqtt_pass))
    {
      Serial.printf("Connected ... announce to broker\n");
      mqttClient.publish(get_topic_name(PUBLIC_PUBLISH, "announce"), buf_data);
    }
    else
    {
      /* Wait 5 seconds before retry */
      delay(5000);
    }
  }
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Are we connected */
  if (WiFiMulti.run() == WL_CONNECTED)
  {
    mqttClient.loop();
    /* This delay fixes some issues with WiFi stability and data loss */
    delay(10);

    /* Maintain a connection with the MQTT broker */
    if (!mqttClient.connected())
    {
      mqtt_connect();
    }

    /* Get the sensor data into our structure */
    if (get_sensor_data(&sdata))
    {
      Serial.printf("Error while reading sensors data\n");
      return;
    }

    /* If more than 2.5s passed since last message, sent another one */
    millis_now = millis();
    if (millis_now - millis_last > 2500)
    {
      /* Refresh timer */
      millis_last = millis_now;

      /* Upload structure data to MQTT broker */
      if (upload_sensor_data(&sdata))
      {
        Serial.printf("Error while uploading sensors data\n");
        return;
      }
    }
  }
}
