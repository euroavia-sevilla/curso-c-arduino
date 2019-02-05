# Electronica necesaria relacionada con Arduino

## Placa base: D1 Mini (WeMoS, NodeMCU)

![Vista frontal y trasera de la PCB: D1 Mini](media/D1-Mini_top-bottom.jpg)

Pagina oficial de la placa [wemos.cc](https://wiki.wemos.cc/products:d1:d1_mini)

Basada en el chip [ESP8266EX](media/ESP8266EX_datasheet_en.pdf)

Caracteristicas:

![Resumen de caracteristicas del chip ESP8266ES](media/ESP8266EX_specs-table.png)

## Tablas comparativas de precios por tipo de modulo

Para poder calcular adecuadamente los gastos se ha hecho una busqueda de los elementos que sirven o puedan servir para el proyecto.

Se han ordenado por precio unitario de menor a mayor, y se ha incluido la columna del vendedor para el caso que se intente comprar por lote.

Debido al precio o a la tardanza del envio, apenas se muestran modulos compatibles directamente con el D1 (apilado vertical). La forma de conectarlos a la placa base sera mediante cableado o una PCB de adaptacion (es posible hacerla mediante placas pre-taladradas de prototipado: [Genericas](https://www.amazon.es/s/ref=nb_sb_noss_2?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&url=search-alias%3Daps&field-keywords=pcb+prototipo&rh=i%3Aaps%2Ck%3Apcb+prototipo) o [compatibles con D1 mini](https://www.amazon.es/dp/B07F6C3DF8/ref=cm_sw_r_tw_dp_U_x_3qiwCbSAV2RZA))

La ventaja de los modulos con linea unica es que pueden montarse en vertical sin nigun problema, por lo que se pueden condensar varias placas en la vertical de la placa base.

Las medidas se dan pensando en que la placa base estara puesta de forma horizontal y el resto de placas esclavo en vertical. Por esto ultimo, el ancho de la placa se basara en el lado en el que se apoya (el lado donde existan pines) y el alto se medira sobre uno de los lados contiguos al ancho.

### Placa base: D1 Mini

![Render de placa base: D1 Mini](media/3D/ESP8266_D1-Mini.stl)

| Vendedor   | Item    | Cantidad | Precio  | Precio Ud. | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:    | :-----: | :-----:  | :-----: | :-----:    | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| IZOKEE     | D1 Mini | 5        | 22.99   | 4.6        | 25.6       | 34.2      | 10          | 3        | [Link](https://www.amazon.es/dp/B076F81VZT/ref=cm_sw_r_tw_dp_U_x_FnhwCbJXNS727) |
| IZOKEE     | D1 Mini | 3        | 14.99   | 5          | 25.6       | 34.2      | 10          | 3        | [Link](https://www.amazon.es/dp/B076F53B6S/ref=cm_sw_r_tw_dp_U_x_Y5hwCbAY80Q19) |
| AZDelivery | D1 Mini | 5        | 24.99   | 5          | 25.6       | 34.2      | 10          | 3        | [Link](https://www.amazon.es/dp/B0754W6Z2F/ref=cm_sw_r_tw_dp_U_x_v5hwCbSC78N0C) |
| AZDelivery | D1 Mini | 3        | 17.99   | 6          | 25.6       | 34.2      | 10          | 3        | [Link](https://www.amazon.es/dp/B0754N794H/ref=cm_sw_r_tw_dp_U_x_17hwCbJE01X3R) |

### Placa esclavo 1: Micro-SD para data-logger

![Render de placa esclavo 1: uSD Data Logger](media/3D/breakout_uSD.step)

| Vendedor  | Item                      | Cantidad | Precio  | Precio Ud. | Pinout compatible D1 Mini | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:   | :-----:                   | :-----:  | :-----: | :-----:    | :-----:                   | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| ILS       | Modulo uSD con 1xLDO      | 10       | 12.69   | 1.27       | No, linea doble           | 30         | 51        | 10          | 8        | [Link](https://www.amazon.es/dp/B079124Z4G/ref=cm_sw_r_tw_dp_U_x_9kgwCbS7D4XS3) |
| Electrely | Modulo uSD con 2xLDO      | 5        | 8.99    | 1.80       | No, linea unica           | 24         | 42        | 12          | 5        | [Link](https://www.amazon.es/dp/B07G296J2M/ref=cm_sw_r_tw_dp_U_x_RjgwCbAC8SWAE) |
| TECNOIOT  | Modulo uSD con 2xLDO      | 5        | 9.48    | 1.90       | No, linea unica           | 24         | 42        | 12          | 5        | [Link](https://www.amazon.es/dp/B07LH6DH9D/ref=cm_sw_r_tw_dp_U_x_plgwCb481VT7A) |
| ILS       | Modulo Wemos uSD (no LDO) | 5        | 13.29   | 2.66       | Si                        | 25.6       | 34.2      | 10          | 10       | [Link](https://www.amazon.es/dp/B07F6CF6YD/ref=cm_sw_r_tw_dp_U_x_FZfwCbXXAGKNK) |

### Placa esclavo 2: Sensor de temperatura y humedad

![Render de placa esclavo 1: DHT11](media/3D/breakout_DHT11.step)

| Vendedor | Item               | Cantidad | Precio  | Precio Ud. | Pinout compatible D1 Mini | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:  | :-----:            | :-----:  | :-----: | :-----:    | :-----:                   | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| DollaTek | Modulo DHT11       | 5        | 8.99    | 1.8        | No, linea unica           | 12         | 28        | 10          | 5        | [Link](https://www.amazon.es/dp/B07DK8MVNX/ref=cm_sw_r_tw_dp_U_x_FagwCbN7YP2E2) |
| ILS      | Modulo Wemos DHT12 | 10       | 26.99   | 2.7        | Si                        | 25.6       | 34.2      | 10          | 10       | [Link](https://www.amazon.es/dp/B07FCJY5FZ/ref=cm_sw_r_tw_dp_U_x_hYfwCbA1C7WDR) |

### Placa esclavo 3: Sensor barometrico

![Render de placa esclavo 1: BMP180](media/3D/breakout_BMP180.step)

| Vendedor    | Item          | Cantidad | Precio  | Precio Ud. | Pinout compatible D1 Mini | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:     | :-----:       | :-----:  | :-----: | :-----:    | :-----:                   | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| MissBirdler | Modulo BMP180 | 5        | 14.49   | 2.9        | No, linea unica           | 10         | 12        | 5           | 1        | [Link](https://www.amazon.es/dp/B07GNKWWWF/ref=cm_sw_r_tw_dp_U_x_BggwCbCETKDP7) |
| AZDelivery  | Modulo BMP280 | 5        | 15.96   | 3.2        | No, linea unica           | 15.5       | 12.2      | 5           | 1        | [Link](https://www.amazon.es/dp/B07HMWB4PD/ref=cm_sw_r_tw_dp_U_x_gfgwCbZTN68BG) |

### Placa esclavo 2 + 3: Sensor de temperatura, humedad y presion

![Render de placa esclavo 1: BME280](media/3D/breakout_BME280.step)

| Vendedor   | Item          | Cantidad | Precio  | Precio Ud.         | Pinout compatible D1 Mini | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:    | :-----:       | :-----:  | :-----: | :-----:            | :-----:                   | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| AZDelivery | Modulo BME280 | 5        | 26.12   | 5.23 (+0.53/-0.67) | No, linea unica           | 10         | 12        | 5           | 1        | [Link](https://www.amazon.es/dp/B07HMQMW6M/ref=cm_sw_r_tw_dp_U_x_BDhwCbJR0T7HB) |
| diymore    | Modulo BME280 | 5        | 26.99   | 5.4 (+0.7/-0.5)    | No, linea unica           | 10         | 12        | 5           | 1        | [Link](https://www.amazon.es/dp/B0799FH5PG/ref=cm_sw_r_tw_dp_U_x_0DhwCbT54YETR) |

### Placa esclavo 4: Giroscopo de 3 ejes y acelerometro de 3 ejes

![Render de placa esclavo 1: MPU-6050](media/3D/breakout_MPU6050a.step)

![Render de placa esclavo 1: MPU-6050](media/3D/breakout_MPU6050b.step)

| Vendedor    | Item            | Cantidad | Precio  | Precio Ud. | Pinout compatible D1 Mini | Ancho (mm) | Alto (mm) | Grosor (mm) | Peso (g) | Link Amazon                                                                     |
| :-----:     | :-----:         | :-----:  | :-----: | :-----:    | :-----:                   | :-----:    | :-----:   | :-----:     | :-----:  | :-----:                                                                         |
| MUZOCT      | Modulo MPU-6050 | 6        | 14.29   | 2.4        | No, linea unica           | 20         | 16        | 5           | 1        | [Link](https://www.amazon.es/dp/B07D7SSTFW/ref=cm_sw_r_tw_dp_U_x_iWhwCbYCAJV6C) |
| Kuman       | Modulo MPU-6050 | 10       | 31.99   | 3.2        | No, linea unica           | 20         | 16        | 5           | 1        | [Link](https://www.amazon.es/dp/B01N96D51D/ref=cm_sw_r_tw_dp_U_x_WOhwCbS8G4XTD) |
| Gikfun      | Modulo MPU-6050 | 3        | 13.31   | 4.43       | No, linea unica           | 20         | 16        | 5           | 1        | [Link](https://www.amazon.es/dp/B07FVKWJF6/ref=cm_sw_r_tw_dp_U_x_SUhwCbPK351RC) |
| MissBirdler | Modulo MPU-6050 | 3        | 13.37   | 4.46       | No, linea unica           | 20         | 16        | 5           | 1        | [Link](https://www.amazon.es/dp/B07GNJLN46/ref=cm_sw_r_tw_dp_U_x_VRhwCbA2Q11TK) |