# Práctica 3 - Uso de librerías

Tras aprender lo que es el bus I2C y como acceder a los datos en bruto de un dispositivo, en esta práctica se usará una libreria para que haga ese mismo trabajo.

Esto supone una primera ventaja clara: en lugar de necesitar saber los pormenores de un chip, ahora solo será necesario saber cómo se usan las funciones de una librería.

## Introducción

Una libreria es uno o varios ficheros de código en donde ya hay programadas ciertas funcionalidades y se incluyen en el código en forma de paquete, lo que:

* Simplificará enormemente el proceso de desarrollo
* Incrementará la calidad y legibilidad del código final
* Necesitará de mucho menos tiempo para obtener los mismos resultados
* Evitará errores innecesarios, pues normalmente han pasado muchas pruebas
* Si una libreria falla suele haber alternativas

Aunque no se haya estudiado en profundidad, esto ya se ha utilizado en los programas del taller en el momento que se usa, por ejemplo, `#include <Wire.h>`.

Lo que realmente se está haciendo es incluir la cabecera de la librería `Wire`, que dará a conocer al programa una serie de variables, funciones, clases, etc. De esta forma pasan a estar disponibles, y por lo tanto, su funcionalidad.

Dicho de otro modo, la librería `Wire` evita tener que leer uno o varios datasheets de un microcontrolador para saber cómo hacer funcionar el bus I2C en su forma mas basica.

> Sin la libreria `Wire` sería necesario programar funciones como `Wire.requestFrom()` o `Wire.read()`, lo que haría prácticamente inviable desarrollos a corto plazo.

La siguiente figura muestra el modelo de capas de abstracción que se está usando:

![abstraction-layers.png](abstraction-layers.png)

Para el caso del sensor BME280, supondría una gran ventaja disponer de una librería que ya hiciera todo el trabajo de pedir los datos y convertirlos, con tan solo definir los parámetros básicos del bus I2C y dirección de esclavo ... y es lo que se verá a continuación.

## Como continuar

Lo primero es buscar y estudiar las posibilidades, y para esto Arduino facilita la tarea mediante un gestor de librerias, al que se accede a través de *Herramientas > Gestor de librerias ...*, obteniendo algo como en la siguiente figura:

![arduino-library-manager.png](arduino-library-manager.png)

Como se continuará con el sensor BME280, se pone como filtro de búsqueda, lo que resultará en algo como:

![arduino-library-manager_BME280.png](arduino-library-manager_BME280.png)

> Para la práctica se ha seleccionado la de **SparkFun Electronics**, por ser una de las mas completas, configurables y robustas. Esto no significa que no se pueda buscar información del resto, probarlas, y sacar conclusiones propias.

## Práctica

Una vez visto el mecanismo de instalación y uso de librerías, se proporcionan los siguientes ejemplos para cada parte interesante del dispositivo, con vistas a utilizar todos o parte de los elementos para la última práctica, donde se construirá un nodo IoT WiFi completamente funcional.

Se recomienda compilar, probar y salvar cada ejemplo, para asi ver las particularidades de cada uno, y tomar consciencia del trabajo que pueda necesitar unificar todo en un único programa.


### BME280: Temperatura, Humedad, Presión, Altitud

#### Resumen

La libreria propuesta se encarga de todo el proceso de bajo nivel encargado de pedir los datos en bruto y procesarlos. El programador solo tendrá que pedir los datos, obteniendolos ya convertidos y en `float`.

Se instala desde el gestor de librerias interno de Arduino.

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `SparkFun BME280` de *SparkFun Electronics* | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library) | Documentado con ejemplos | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library/tree/master/examples) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library/tree/master/src) |

#### Ejemplo funcional

```C
/* Include required headers and/or libraries */
#include <Wire.h>
#include "SparkFunBME280.h"

#define SLAVE_ADDRESS 0x76

/* Instantiate a BME280 object called BME280_obj */
BME280 BME280_obj;

/*
 * Single-pass function to configure the app
 */
void setup()
{
  /* Start serial for output */
  Serial.begin(115200);

  /* Join I2C bus and set it to 400 kHz */
  Wire.begin(0, 2);
  Wire.setClock(400000);

  /* Address the sensor */
  BME280_obj.setI2CAddress(SLAVE_ADDRESS);

  /* Check communication before continue */
  if (BME280_obj.beginI2C(Wire) == false)
  {
    Serial.printf("The sensor did not respond. Please check wiring.\n");
    
    /* Stop here (WDT will reset at some point) */
    while(1);
  }

  /* -- Configure the sensor --
   *  - Read  the  datasheet -
   */
  /* Filter coefficient.          | 0 to 4 is valid.   | See 3.4.4     */
  BME280_obj.setFilter(2);
  /* Time between readings.       | 0 to 7 valid.      | See table 27. */
  BME280_obj.setStandbyTime(1);
  /* 0 disables temp sensing.     | 0 to 16 are valid. | See table 24. */
  BME280_obj.setTempOverSample(8);
  /* 0 disables pressure sensing. | 0 to 16 are valid. | See table 23. */
  BME280_obj.setPressureOverSample(8);
  /* 0 disables humidity sensing. | 0 to 16 are valid. | See table 19. */
  BME280_obj.setHumidityOverSample(8);
  /* MODE_SLEEP, MODE_FORCED, MODE_NORMAL is valid.    | See 3.3       */
  BME280_obj.setMode(MODE_NORMAL);
}

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Welcome message! Useful as a control point */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Read and print sensor data */
  Serial.printf(" - Temp.: %2.2f [C]\n",  BME280_obj.readTempC());
  Serial.printf(" - Temp.: %2.2f [F]\n",  BME280_obj.readTempF());
  Serial.printf(" - Hum..: %2.2f [%%]\n", BME280_obj.readFloatHumidity());
  Serial.printf(" - Pres.: %2.2f [Pa]\n", BME280_obj.readFloatPressure());
  Serial.printf(" - Alt..: %2.2f [m]\n",  BME280_obj.readFloatAltitudeMeters());
  Serial.printf(" - Alt..: %2.2f [Ft]\n", BME280_obj.readFloatAltitudeFeet());

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
 - Temp.: 34.08 [C]
 - Temp.: 93.34 [F]
 - Hum..: 26.10 [%]
 - Pres.: 101292.66 [Pa]
 - Alt..: 2.69 [m]
 - Alt..: 8.83 [Ft]
Ahoy! ESP8266 here!
---
 - Temp.: 34.05 [C]
 - Temp.: 93.29 [F]
 - Hum..: 26.04 [%]
 - Pres.: 101292.16 [Pa]
 - Alt..: 2.73 [m]
 - Alt..: 8.97 [Ft]
```


### MPU6050: Temperatura, Aceleración, Rotación

#### Resumen

La libreria propuesta se encarga de hacer el trabajo de bajo nivel de pedir datos y convertirlos, aunque queda para el programador la puesta a 0 y corrección de offset.

Se han probado librerias en principio mas completas, pero que en el momento de la ejecución fallaban o no conseguian una comunicación adecuada con el sensor.

Se instala desde el gestor de librerias interno de Arduino.

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `MPU6050` de *Electronic Cats* | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio](https://github.com/electroniccats/mpu6050) | Documentado con ejemplos | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://github.com/electroniccats/mpu6050/tree/master/examples) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/electroniccats/mpu6050/tree/master/src) |

#### Ejemplo funcional

```C
/* Include required headers and/or libraries */
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define MPU6050_ADDRESS 0x68

/* Instantiate a MPU6050 object called MPU6050_obj */
MPU6050 accelgyro(MPU6050_ADDRESS);

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
  Wire.begin(0, 2);
  Wire.setClock(400000);

  /* Initialize the sensor */
  accelgyro.initialize();

  /* Check communication before continue */
  if (accelgyro.testConnection() == false)
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
  //accelgyro.setFullScaleGyroRange(MPU6050_range[RANGE_GYRO].current);

  /* Configure Accelerometer range, choose from:
   * - MPU6050_ACCEL_FS_2 ...: +/-2g
   * - MPU6050_ACCEL_FS_4 ...: +/-4g
   * - MPU6050_ACCEL_FS_8 ...: +/-8g
   * - MPU6050_ACCEL_FS_16 ..: +/-16g
   *
   * Uncomment the following two lines to set a different value
   */
  //MPU6050_range[RANGE_ACCEL].current = MPU6050_ACCEL_FS_16;
  //accelgyro.setFullScaleAccelRange(MPU6050_range[RANGE_ACCEL].current);
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
                temp_to_human(accelgyro.getTemperature()));
  Serial.printf(" - Rotation X .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             accelgyro.getRotationX()));
  Serial.printf(" - Rotation Y .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             accelgyro.getRotationY()));
  Serial.printf(" - Rotation Z .....: %2.2f [deg/sec]\n",
                raw_to_human(&MPU6050_range[RANGE_GYRO],
                             accelgyro.getRotationZ()));
  Serial.printf(" - Acceleration X .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             accelgyro.getAccelerationX()));
  Serial.printf(" - Acceleration Y .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             accelgyro.getAccelerationY()));
  Serial.printf(" - Acceleration Z .: %2.2f [g]\n",
                raw_to_human(&MPU6050_range[RANGE_ACCEL],
                             accelgyro.getAccelerationZ()));

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
```

#### Salida esperada

> **NOTA:** Sin haberse corregido los offsets, los datos obtenidos pueden no tener sentido, pero lo importante de esta prueba es que varien con coherencia cuando se mueva la placa. La temperatura tambien subira o bajara, aunque en fracciones coherentes.
> 
> Si los datos no varían, el sensor no se está midiendo correctamente.

```text
Ahoy! ESP8266 here!
---
 - Temperature ....: 32.81 [degC]
 - Rotation X .....: 0.24 [deg/sec]
 - Rotation Y .....: 3.66 [deg/sec]
 - Rotation Z .....: -3.87 [deg/sec]
 - Acceleration X .: 0.08 [g]
 - Acceleration Y .: -0.19 [g]
 - Acceleration Z .: 0.83 [g]
Ahoy! ESP8266 here!
---
 - Temperature ....: 32.86 [degC]
 - Rotation X .....: 0.10 [deg/sec]
 - Rotation Y .....: 3.27 [deg/sec]
 - Rotation Z .....: -3.88 [deg/sec]
 - Acceleration X .: 0.08 [g]
 - Acceleration Y .: -0.19 [g]
 - Acceleration Z .: 0.83 [g]
```


### SPIFFS: Ficheros en memoria interna

#### Resumen

Esta librería se encarga de todo el proceso de preparación y uso de una parte de la flash como espacio de almacenamiento de ficheros.

Un caso habitual es la necesidad de salvar información para acceder a ella en otro momento. Se suelen usar chips EEPROM o Flash, o dispositivos externos de almacenamiento, como pendrives.

SPIFFS surge como una solución para poder compartir el mismo espacio de almacenamiento que se usa para el programa, pero para el uso indiscriminado como almacenamiento de ficheros, lo que ahorra la necesidad de un chip extra, simplificando tanto el circuito como el programa finales.

> **NOTA:** Es necesario **configurar Arduino** para que asigne algo de espacio para SPIFFS. Esto se hace en la configuración de la placa, donde se usará la opcion de `1 Mb para Programa y 3 Mb para SPIFFS`, ya que inicialmente el programa no llegará a ocupar 1 Mb. En caso de ser asi, sera necesario modificar esta opción.
> 
> **NOTA:** Es posible que tras programar la placa, esta no se arranque bien y quede en un estado errático. Sólo se deberá resetear con el pulsador lateral, y esperar el mensaje `Initializing SPIFFS`. El primer arranque **podrá tardar bastante**, ya que está preparando el espacio, pero a partir del segundo arranque, todo será casi instantáneo.

En este caso no es una libreria instalable de forma individual, ya está instalada como parte del soporte para ESP8266, por lo que para su uso sólo será necesario incluir la cabecera.

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `FS` de *Ivan Grokhotkov* | [<i class="fa fa-link" style="color:#FA023C"></i>Repositorio (FS.h)](https://github.com/esp8266/Arduino/blob/2.5.0/cores/esp8266/FS.h) | [<i class="fa fa-link" style="color:#FA023C"></i> Documentación](https://arduino-esp8266.readthedocs.io/en/2.5.0/filesystem.html) | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplo](https://github.com/esp8266/Arduino/blob/2.5.0/libraries/esp8266/examples/ConfigFile/ConfigFile.ino) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/esp8266/Arduino/blob/2.5.0/cores/esp8266/FS.cpp) |

#### Ejemplo funcional

```C
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
```

#### Salida esperada

```text
Initializing SPIFFS
Ahoy! ESP8266 here!
---
File '/test_file.txt'' NOT found'
Opened '/test_file.txt'
Filling file '/test_file.txt' with some data
Contents of file '/test_file.txt'
Line 000: This is the first line
Line 001: This is the second line
Line 002: This is the third line
Closed '/test_file.txt'
Removed '/test_file.txt'
Locking now
```


### WiFi: Conexión a red y petición HTTP usando TCP

#### Resumen

Esta libreria permite conectar el dispositivo a redes WiFi, y por tanto, a servidores mediante TCP, UDP, ...

Se tendrá que definir la red a la que conectar, y su password. Una vez esté el dispositivo conectado se podrá comenzar una conexión TCP, como se muestra en el ejemplo.

En este caso no es una libreria instalable de forma individual, ya está instalada como parte del soporte para ESP8266, por lo que para su uso sólo será necesario incluir la cabecera.

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `ESP8266WiFi.h` | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio (ESP8266WiFi.h)](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h) | [<i class="fa fa-link" style="color:#FA023C"></i> Documentación](https://arduino-esp8266.readthedocs.io/en/2.5.0/esp8266wifi/readme.html) | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/src) |

#### Ejemplo funcional

```C
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
```

#### Salida esperada

En el caso del router `IoTesla` usado en el taller, pueden darse dos situaciones: Cuando envíe contenido o cuando sólo mantenga la conexión.

Manteniendo la conexión activa:

```text
Ahoy! ESP8266 here!
---
Connecting to 'IoTesla' access point [........]
Connected! Assigned IP: 192.168.1.245
Connecting to 192.168.1.1:80 ... Done!
Requesting /index.html
Response received:
Printing 41 bytes ---
HTTP/1.1 200 OK
Connection: Keep-Alive

---
Closing connection. Reloop in 10 seconds ...
```

Contenido de `/index.html`:

```text
Ahoy! ESP8266 here!
---
Connecting to 'IoTesla' access point [........]
Connected! Assigned IP: 192.168.1.245
Connecting to 192.168.1.1:80 ... Done!
Requesting /index.html
Response received:
Printing 577 bytes ---
HTTP/1.1 200 OK
Connection: Keep-Alive
Keep-Alive: timeout=20
ETag: "3dc-1ef-59e641ec"
Last-Modified: Tue, 17 Oct 2017 17:46:20 GMT
Date: Wed, 10 Apr 2019 16:34:12 GMT
Content-Type: text/html
Content-Length: 495

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Cache-Control" content="no-cache" />
<meta http-equiv="refresh" content="0; URL=/cgi-bin/luci" />
</head>
<body style="background-color: white">
<a s
---
Closing connection. Reloop in 10 seconds ...
```


### WiFiMulti: Conectividad entre redes

#### Resumen

Esta libreria incrementa las posibilidades de la libreria WiFi al automatizar el proceso de mantener la conectividad siempre que sea posible. Se encargará de intentar la conexion a una red y mantenerla, y en caso de perderse, repetira el proceso con otra de las redes configuradas, hasta que recupere la conectividad.

El programador sólo tendrá que definir las redes que conocerá el dispositivo, con sus passwords en caso de necesitarse, y luego llamar al metodo `.run()` en el loop principal para mantener actualizado el estado de la libreria.

Esto facilitará la tarea de utilizarlo en el taller, en casa, en el trabajo ... con solo configurar una sola vez las posibles redes que tendrá disponibles en algún momento.

En este caso no es una libreria instalable de forma individual, ya está instalada como parte del soporte para ESP8266, por lo que para su uso sólo será necesario incluir la cabecera.

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `ESP8266WiFiMulti` de *Markus Sattler* | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio (ESP8266WiFiMulti.h)](https://github.com/esp8266/Arduino/blob/2.5.0/libraries/ESP8266WiFi/src/ESP8266WiFiMulti.h) | Documentado en ejemplos | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-examples.html#introduction) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/esp8266/Arduino/blob/2.5.0/libraries/ESP8266WiFi/src/ESP8266WiFiMulti.cpp) |

#### Ejemplo funcional

```C
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

  /* Ensure to work as Station (disables internal AP) */
  WiFi.mode(WIFI_STA);

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
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
scandone
Returned WL_DISCONNECTED
Returned WL_NO_SSID_AVAIL
Returned WL_NO_SSID_AVAIL
Returned WL_NO_SSID_AVAIL
Returned WL_NO_SSID_AVAIL
scandone
scandone
state: 0 -> 2 (b0)
state: 2 -> 3 (0)
state: 3 -> 5 (10)
add 0
aid 3
cnt 

connected with IoTesla, channel 9
dhcp client start...
ip:192.168.1.245,mask:255.255.255.0,gw:192.168.1.1
Returned WL_CONNECTED
Returned WL_CONNECTED
Returned WL_CONNECTED
Returned WL_CONNECTED
Returned WL_CONNECTED
Returned WL_CONNECTED
Returned WL_CONNECTED
```


### PubSubClient: Cliente MQTT (I)

Se pretende conseguir un cliente MQTT estable y con un indice de fallos lo mas próximo a 0% posible. Se ponen a prueba dos librerias ampliamente aceptadas en la comunidad Arduino: *PubSubClient* y *MQTT*.

PubSubClient permite utilizar MQTT de una forma sencilla, permitiendo seleccionar entre el protocolo 3.1 o 3.1.1. No permite conexiones seguras y sus publicaciones se enviarán con QoS = 0, por lo que no habrá confirmación de entrega.

Está muy aceptada por la comunidad, tiene un buen soporte y una extensa documentación, aparte de muchos ejemplos funcionales. En las pruebas ha funcionado a la perfección.

> **NOTA:** Aunque no se ha encontrado una documentación mas amplia donde se explique con detalle, es obligatorio incluir un retraso tras el loop del cliente, ya que de lo contrario los envios no funcionarán.
>
> En el ejemplo se incluye de la siguiente manera:

```C
...
    mqttClient.loop();
    /* This delay fixes some issues with WiFi stability and data loss */
    delay(10);
...
```

Se instala desde el gestor de librerias interno de Arduino.

#### Resumen

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `PubSubClient` de *Nick O'Leary* | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio](https://github.com/knolleary/pubsubclient) | [<i class="fa fa-link" style="color:#FA023C"></i> Documentación](https://pubsubclient.knolleary.net/index.html) | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://github.com/knolleary/pubsubclient/tree/master/examples) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/knolleary/pubsubclient/tree/master/src) |

#### Ejemplo funcional

```C
/* Include required headers and/or libraries */
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
/* https://github.com/knolleary/pubsubclient */
#include <PubSubClient.h>

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
PubSubClient mqttClient(mqtt_host, mqtt_port, espClient);

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
                "> Testing: knolleary's PubSubClient.h library\n"
                "---\n"
                );

  /* Ensure to work as Station (disables internal AP) */
  WiFi.mode(WIFI_STA);

  /* Add your home/personal wifi here */
  WiFiMulti.addAP("personal-wifi", "the_password");

  /* If not found, will try to connect to this one */
  WiFiMulti.addAP("IoTesla",       "euroavia2019");
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
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
> Testing: knolleary's PubSubClient.h library
---
Connecting to MQTT broker:
 - username ..: tc_d1_0000
 - client ID .: IoTesla-007FEA27-001640EF

Connected ... announce to broker
Sensor data published ... OK
Sensor data published ... OK
Sensor data published ... OK
```


### MQTT: Cliente MQTT (II)

Esta es la segunda librería bajo prueba, teniendo tambien un gran soporte un desarrollo muy activo.

Permite conexiones seguras y mensajes con QoS superior a 0. Todo esto aportará al tamaño final del binario, pero en caso de necesitarse, se puede usar.

Funciona a la perfección y tiene una API casi idéntica a la anterior libtería, por lo que la migración entre ellas es muy simple.

> **NOTA:** Aunque no se ha encontrado una documentación mas amplia donde se explique con detalle, es obligatorio incluir un retraso tras el loop del cliente, ya que de lo contrario los envios no funcionarán.
>
> En el ejemplo se incluye de la siguiente manera:

```C
...
    mqttClient.loop();
    /* This delay fixes some issues with WiFi stability and data loss */
    delay(10);
...
```

Se instala desde el gestor de librerias interno de Arduino.

#### Resumen

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `MQTT` de *Joel Gaehwiler* | [<i class="fa fa-link" style="color:#FA023C"></i> Repositorio](https://github.com/256dpi/arduino-mqtt) | Documentado en web y ejemplos | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplos](https://github.com/256dpi/arduino-mqtt/tree/master/examples) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/256dpi/arduino-mqtt/tree/master/src) |

#### Ejemplo funcional

```C
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
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
> Testing: 256dpi's MQTT.h library
---
Connecting to MQTT broker:
 - username ..: tc_d1_0000
 - client ID .: IoTesla-007FEA27-001640EF

Connected ... announce to broker
Sensor data published ... OK
Sensor data published ... OK
Sensor data published ... OK
```
