# Práctica 2 - El bus I2C

# Introducción

Antes de comenzar, se debe entender el concepto de bus:

> De [Wikipedia](https://es.wikipedia.org/wiki/Bus_(inform%C3%A1tica)):
> 
> En arquitectura de computadores, el **bus** (o canal) es un sistema digital que transfiere datos entre los componentes de una computadora. Está formado por cables o pistas en un circuito impreso, dispositivos como resistores y condensadores, además de circuitos integrados.
> 
> Existen dos tipos de transferencia en los buses:
> 
> * Serie: El bus solamente es capaz de transferir los datos bit a bit. Es decir, el bus tiene un único cable que transmite la información.
> * Paralelo: El bus permite transferir varios bits simultáneamente, por ejemplo 8 bits.
> 
> Aunque en primera instancia parece mucho más eficiente la transferencia en paralelo, esta presenta inconvenientes:
> 
> * La frecuencia de reloj en el bus paralelo tiene que ser más reducida.
> * La longitud de los cables que forman el bus está limitada por las posibles interferencias, el ruido y los retardo en la señal.
> 
> Además, los modernos buses serie están formados por varios canales: En este caso se transmite por varios buses serie simultáneamente. 

El **bus I2C** surge como una solución de comunicación entre chips, denominandose *Inter Integrated Circuits* bus o IIC, acabando posteriormente como I2C.

Es una norma que especifica la velocidad, niveles de tensión, y el protocolo a seguir para conseguir esa comunicación.

Se basa en una comunicación de tipo Maestro-Esclavo, donde varios chips se conectan en paralelo compartiendo las lineas de alimentación y dos específicas, SCL (Linea de reloj) y SDA (Linea de datos), como se ve en la siguiente figura:

![Diagrama de conexión I2C](I2C-diagram.jpg)

El maestro, cuando quiera iniciar una comunicación, establecerá una frecuencia en la línea de SCL, que normalmente será 100 kHz o 400 kHz, e iniciará la comunicación como corresponda a traves de la linea SDA.

Dicha comunicación se hará localizada a un chip concreto, mediante su dirección de esclavo de 7 bits. Esto hace que el bus admita hasta 128 dispositivos.

Para no alargar la introducción entrando en detalles técnicos de nivel mas bajo, en caso de querer saberlos se deja como referencia el documento oficial de NXP (antes Philips).

> Descargar [<i class="fa fa-cloud-download-alt" style="color:#FA023C"></i> I2C-bus specification and user manual (UM10204)](UM10204.pdf)

## Práctica

En esta práctica se busca conseguir una comunicación a traves del bus I2C con los dispositivos I2C acoplados al D1 Mini:

* [BME280](../../hardware/#sensor-bme280-temperatura-humedad-y-presion): Sensor de temperatura, humedad y presión
* [MPU6050](../../hardware/#sensor-mpu6050-giroscopo-de-3-ejes-y-acelerometro-de-3-ejes): Giroscopo de 3 ejes y acelerometro de 3 ejes

El montaje proporcionado equivale al siguiente esquemático:

![D1-and-sensors.png](../../hardware/D1-and-sensors.png)

La librería I2C, en Arduino se llama Wire, y gestiona el protocolo de comunicaciones completo, lo que es un detalle, pues nos ahorra la parte de estudiar el protocolo y escribir programas para ello (maquina de estados a bajo nivel).

* Esto es una practica habitual y recomendada, construir sobre el trabajo de terceros. Es una de las muy grandes virtudes de la comunidad Arduino y open source.
* Hay una gama muy amplia de librerias que dan soporte a muchisimos dispositivos, o crean funcionalidades nuevas, ...
* Se recomienda buscar, probar y sacar conclusiones para ver tanto la calidad como el posible uso.

## Programa

Se parte de la anterior sesión, donde un programa enviaba por puerto serie 3 variables, para luego verlas o dibujarlas mediante el monitor serie o el plotter, respectivamente.

> **Librerias ESP8266 para Arduíno**: Se debe consultar para saber como manejar los periféricos del micro. Disponible en [https://arduino-esp8266.readthedocs.io/en/latest/libraries.html](https://arduino-esp8266.readthedocs.io/en/latest/libraries.html)

> **Libreria `Wire` de Arduino**: Una vez vistos los pormenores de la parte especifica para ESP8266, se debe consultar esta para conocer el manejo genérico en todos los Arduino. Disponible en [https://www.arduino.cc/en/reference/wire](https://www.arduino.cc/en/reference/wire)

Para poder comenzar con el uso de las funciones de I2C es necesario incluir la cabecera de la libreria `Wire`, al principio de nuestro programa, de la siguiente forma:

```C
/* Include required headers and/or libraries */
#include <Wire.h>
```

Incluir su inicialización en la sección de setup:

```C
/* Single-pass function to configure the app */
void setup()
{
  /* Join i2c bus (address optional for master) */
  Wire.begin(0, 2);

  /* start serial for output */
  Serial.begin(115200);
}
```

Y por último, pedir un dato a algún dispositivo esclavo en el bucle principal, mostrándolo por pantalla para saber que está bien:

```C
/* Recurrent task, called forever */
void loop()
{
  /* Welcome message! Useful to know where  */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Request data from slave with address 0x12 */
  Wire.requestFrom(0x12, 1);

  /* Receive the byte */
  uint8_t c = Wire.read();

  /* Send it to console/monitor */
  Serial.printf("Received byte: %02X\n", c);

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
```

Al lanzar el programa no será posible una comunicación, al no existir un esclavo con la dirección `0x12`, lo que llevará al siguiente paso: Estudiar los dispositivos

En el caso del BME280, tras leer su datasheet, vemos como la dirección asociada será `0x76` o `0x77`, segun si uno de sus pines está puesto a GND o a Vcc. En el caso de la placa de prácticas, este pin está en GND por lo que la dirección final queda como `0x76`.

Otro punto a tener en cuenta es que no se está controlando la disponibilidad de datos, y se pide su lectura como si esto fuera un hecho, pero lo cierto es que es posible que el dispositivo aun no responda, por lo que el dato se acabaría perdiendo. Para esto existe `Wire.available()`.

Incluyendo ambos datos, nuestro nuevo programa quedaría como:

```C
/* Include required headers and/or libraries */
#include <Wire.h>

/* Single-pass function to configure the app */
void setup()
{
  /* Join i2c bus (address optional for master) */
  Wire.begin(0, 2);

  /* start serial for output */
  Serial.begin(115200);
}

/* Recurrent task, called forever */
void loop()
{
  /* Welcome message! Useful to know where  */
  Serial.printf("Ahoy! ESP8266 here!\n---\n");

  /* Request data from slave with address 0x76 */
  Wire.requestFrom(0x76, 1);

  /* Wait for data to be available */
  while (Wire.available())
  {
    /* Receive the byte */
    uint8_t c = Wire.read();

    /* Send it to console/monitor */
    Serial.printf("Received byte: %02X\n", c);
  }

  /* Ensure not to flood with a huge amount of fast data */
  delay(500);
}
```

Si nos fijamos bien, no estamos controlando qué dato pedimos, simplemente "leemos un byte". Para poder pedir un dato concreto y controlado, es necesario direccionarlo primero.

Es tarea del alumno continuar a partir de aqui, confirmando primero una comunicación adecuada, y obteniendo posteriormente los datos de temperatura, humedad y presión (necesitando por tanto recibir mas de un byte en una tanda).

Estos datos se presentarán por pantalla tras su lectura, como ha quedado reflejado en el ejemplo.

> **NOTA**: Para confirmar la comunicación se suele leer primero un byte conocido, que para el caso del BME280 es el identificador del chip, o **Chip ID**. [Ver la sección dedicada al BME280](../../hardware/#sensor-bme280-temperatura-humedad-y-presion) para mas información.

El siguiente paso, será comunicarnos con el MPU-6050 de la misma forma.
 