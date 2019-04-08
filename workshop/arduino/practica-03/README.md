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
  Wire.begin();
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

| Libreria | Enlaces de interés | | | |
| :----- | :-----: | :-----: | :-----: | :-----: |
| `FS` de *Ivan Grokhotkov* | [<i class="fa fa-link" style="color:#FA023C"></i>Repositorio (FS.h)](https://github.com/esp8266/Arduino/blob/2.5.0/cores/esp8266/FS.h) | [<i class="fa fa-link" style="color:#FA023C"></i> Documentación](https://arduino-esp8266.readthedocs.io/en/2.5.0/filesystem.html) | [<i class="fa fa-link" style="color:#FA023C"></i> Ejemplo](https://github.com/esp8266/Arduino/blob/2.5.0/libraries/esp8266/examples/ConfigFile/ConfigFile.ino) | [<i class="fa fa-link" style="color:#FA023C"></i> Código fuente](https://github.com/esp8266/Arduino/blob/2.5.0/cores/esp8266/FS.c) |

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

