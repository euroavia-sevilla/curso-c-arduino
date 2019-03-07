# euroavia-c-arduino
Contenido relacionado con el curso de C y Arduino de (Euroavia)[http://www.euroaviasevilla.es/]

Este repositorio contiene todo lo necesario para el curso de C/Arduino que se impartirá para Euroavia-Sevilla.

Se puede acceder al contenido del curso abriendo la carpeta XXX, pero se recomienda acceder a través de la dirección [https://euroavia-sevilla.github.io/curso-c-arduino/](https://euroavia-sevilla.github.io/curso-c-arduino/), donde el contenido se muestra de una manera mas compacta y clara.

# Contenido

- Software: C
  + [Estandar de C: C99](#estandar-de-c-c99)
  + [Tutorial de C/C++ de tenouk.com](#tutorial-de-cc-de-tenoukcom)
- Hardware: Microcontroladores
  + [Generalidades](#generalidades)
  + [ESP8266](#esp8266)
- Hardware: Sensorica

# Software: C

## Estandar de C: C99

Hay varios estandares que se pueden seguir para programar en C/C++, pero es muy aconsejable ceñirse a C99 mientras sea posible, ya que asegurará una compatibilidad enorme entre diferentes sistemas.

[:page_facing_up: ISO-IEC-9899_C99-Standard.pdf](specs/ISO-IEC-9899_C99-Standard.pdf)

## Tutorial de C/C++ de tenouk.com

**Fuente**: [Link a la pagina de descarga](https://www.tenouk.com/download.html) de donde se han sacado estos PDF

Se incluyen los siguientes ficheros para facilitar la disponibilidad de estos en cada puesto de trabajo.

El usuario solo tendra que utilizar _git_ y descargar la rama para poder acceder a este contenido. Igualmente se enlazan desde aqui para facilitar la navegacion web:

- [:page_facing_up: Module 1. C / C++ Introduction. Intro and history, building and running the first C/C++ program](tutorial-C_tenouk.com/Module1.pdf)
- [:page_facing_up: Module 2. C / C++ Basic Data Types [1/2/3]. The basic C & C++ data types story and program examples](tutorial-C_tenouk.com/Module2.pdf)
- [:page_facing_up: Module 3. C / C++ Statements, Expressions & Operators [1/2/3]. Statements, expressions and operators used in C & C++ story and program examples](tutorial-C_tenouk.com/Module3.pdf)
- [:page_facing_up: Module 4. C / C++ Functions [1/2/3/4]. Functions story and program examples](tutorial-C_tenouk.com/Module4.pdf)
- [:page_facing_up: Module 5. C Formatted I/O [1/2]. The printf() and scanf() story and program examples](tutorial-C_tenouk.com/Module5.pdf)
- [:page_facing_up: Module 6. C / C++ Program Controls [1/2]. Loops, if-else, while, do-while, for, switch-case-break etc. story and program examples](tutorial-C_tenouk.com/Module6.pdf)
- [:page_facing_up: Module 7. C / C++ Arrays [1/2]. Array or aggregated data type, story and program examples](tutorial-C_tenouk.com/Module7.pdf)
- [:page_facing_up: Module 8. C / C++ Pointers [1/2/3]. Pointers, another very important data type, story and program examples](tutorial-C_tenouk.com/Module8.pdf)
- [:page_facing_up: Module 9. C File I/O [1/2/3]. Standard file input/output, creating, reading and writing files, story and program examples](tutorial-C_tenouk.com/Module9.pdf)
- [:page_facing_up: Module 10. C / C++ Preprocessor Directives. Preprocessor directives used in C/C++, #include, macros, inline functions etc](tutorial-C_tenouk.com/Module10.pdf)
- [:page_facing_up: Module 11. C / C++ Type Specifiers. struct, typedef, union & enum - Various C/C++ aggregated data types and typedef](tutorial-C_tenouk.com/Module11.pdf)
- [:page_facing_up: Module W. Assembler, Compiler & Linker. Quite a complete story how C assembled, compiled, linked and run](tutorial-C_tenouk.com/ModuleW.pdf)
- [:page_facing_up: Module X. C's Character and String Manipulation. Using standard C predefined functions in manipulating characters and strings, full of working program examples](tutorial-C_tenouk.com/ModuleX.pdf)
- [:page_facing_up: Module Y. main() and Command Line Arguments. A complete story of the main() function](tutorial-C_tenouk.com/ModuleY.pdf)
- [:page_facing_up: Module Z. C Storage and Memory Allocation. Predefined functions used in memory allocation and de-allocation in C](tutorial-C_tenouk.com/ModuleZ.pdf)

# Hardware: Microcontroladores

## Generalidades

## ESP8266

Extraído de [Wikipedia](https://en.wikipedia.org/wiki/ESP8266)

| ![ESP-01.jpg](media/ESP-01.jpg)] | ESP-01 module by Ai-Thinker                          |
| :-----:                          | :-----:                                              |
| Manufacturer                     | Espressif Systems                                    |
| Type                             | 32-bit microcontroller                               |
| CPU                              | 80 MHz (default) or 160 MHz                          |
| Memory                           | 32 KiB instruction, 80 KiB user data                 |
| Input                            | 16 GPIO pins                                         |
| Successor                        | [ESP32](https://en.wikipedia.org/wiki/ESP32 "ESP32") |

The ESP8266 is a low-cost Wi-Fi microchip with full TCP/IP stack and microcontroller capability produced by manufacturer Espressif Systems in Shanghai, China.

The chip first came to the attention of western makers in August 2014 with the ESP-01 module, made by a third-party manufacturer Ai-Thinker. This small module allows microcontrollers to connect to a Wi-Fi network and make simple TCP/IP connections using Hayes-style commands. However, at first there was almost no English-language documentation on the chip and the commands it accepted. The very low price and the fact that there were very few external components on the module, which suggested that it could eventually be very inexpensive in volume, attracted many hackers to explore the module, chip, and the software on it, as well as to translate the Chinese documentation.

The ESP8285 is an ESP8266 with 1 MiB of built-in flash, allowing for single-chip devices capable of connecting to Wi-Fi.

The successor to these microcontroller chips is the ESP32, released in 2016.

### SDKs

In October 2014, Espressif Systems released a software development kit (SDK) for programming the chip directly, which removed the need for a separate microcontroller. Since then, there have been many official SDK releases from Espressif; Espressif maintains two versions of the SDK -- one that is based on FreeRTOS and the other based on callbacks.

An alternative to Espressif's official SDK is the open-source ESP-Open-SDK that is based on the GCC toolchain, maintained by Max Filippov. Another alternative is the "Unofficial Development Kit" by Mikhail Grigorev.

Other SDKs (mostly open-source) include:

-   [Arduino](https://en.wikipedia.org/wiki/Arduino "Arduino") -- A C++-based firmware. With this core, the ESP8266 CPU and its Wi-Fi components can be programmed like any other Arduino device. The ESP8266 Arduino Core is available through GitHub.
-   ESP8266 BASIC -- An open-source basic interpreter specifically tailored for the internet of things. Self-hosting browser-based development environment.
-   [ESP Easy](https://en.wikipedia.org/wiki/ESP_Easy "ESP Easy") -- Developed by [home automation](https://en.wikipedia.org/wiki/Home_automation "Home automation") enthusiasts.
-   ESP-Open-RTOS -- Open-source FreeRTOS-based ESP8266 software framework.
-   ESP-Open-SDK -- Free and open (as much as possible) integrated SDK for ESP8266/ESP8285 chips.
-   [Espruino](https://en.wikipedia.org/wiki/Espruino "Espruino") -- An actively maintained JavaScript SDK and firmware, closely emulating Node.js. Supports a few MCUs, including the ESP8266.
-   MicroPython -- A port of [MicroPython](https://en.wikipedia.org/wiki/MicroPython "MicroPython") (an implementation of Python for embedded devices) to the ESP8266 platform.
-   [Mongoose OS](https://en.wikipedia.org/wiki/Mongoose_OS "Mongoose OS") -- An open-source operating system for connected products. Supports ESP8266 and ESP32. Develop in C or JavaScript.
-   [NodeMCU](https://en.wikipedia.org/wiki/NodeMCU "NodeMCU") -- A Lua-based firmware.
-   PlatformIO (<https://platformio.org/platforms/espressif8266>) -- A cross-platform IDE and unified debugger, which sits on top of Arduino code and libraries.
-   Smick - Smart brick, based on ESP8266, used to make IoT devices easily using K language.
-   [Sming](https://github.com/SmingHub/Sming) -- An actively developed asynchronous C/C++ framework with superb performance and multiple network features.
-   [uLisp](http://www.ulisp.com/show?21T5) - a version of the [Lisp](https://en.wikipedia.org/wiki/Lisp_(programming_language) "Lisp (programming language)") programming language specifically designed to run on processors with a limited amount of RAM.
-   ZBasic for ESP8266 (<http://www.zbasic.net>) -- A subset of Microsoft's widely used Visual Basic 6, which has been adapted as a control language for the ZX microcontroller family and the ESP8266.
-   Zerynth -- [IoT](https://en.wikipedia.org/wiki/Internet_of_things "Internet of things") framework for programming ESP8266 and other microcontrollers in [Python](https://en.wikipedia.org/wiki/Python_(programming_language) "Python (programming language)").

# Hardware: Sensorica

