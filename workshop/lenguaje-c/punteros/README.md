# Punteros

## Taller

### Ejemplo 1: Punteros simples

En este ejemplo se usan de forma básica los punteros de C. Se verá como se crean y asignan, como se reasignan diréctamente o mediante aritmética simple.

Este ejemplo mostrará una información y se bloqueará. Para poder volver a verla hay que resetear la placa pulsando brevemente el botón de reset lateral.

```C
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

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Create some variables of different types */
  uint8_t  var_u8    =   8;
  int8_t   var_i8    =  -8;
  char     var_ch    = 'c';
  uint16_t var_u16   =  16;
  int16_t  var_i16   = -16;
  uint32_t var_u32   =  32;
  int32_t  var_i32   = -32;
  float    var_flt   = 1.0;
  double   var_dbl   = 2.0;

  /* Create a few arrays */
  uint8_t  arr_u8[8] = {  1,   2,   3,   4,   5,   6,   7,   8  };
  int8_t   arr_i8[8] = { -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8  };
  char     arr_ch[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

  /* Create a few simple (single) pointers */
  uint8_t  *pt_u8    = &var_u8;
  int8_t   *pt_i8    = &var_i8;
  char     *pt_ch    = &var_ch;

  /* Check some variables assignments */
  Serial.printf("Checking variables assignments:\n");
  Serial.printf("(TIP: '@' means 'addressed at')\n");
  Serial.printf(" - Direct-access (using variable name):\n");
  Serial.printf("   - uint8_t  var_u8 ...: %3u @ 0x%X\n", var_u8, &var_u8);
  Serial.printf("   - int8_t   var_i8 ...: %3i @ 0x%X\n", var_i8, &var_i8);
  Serial.printf("   - char     var_ch ...: %3c @ 0x%X\n", var_ch, &var_ch);
  Serial.printf("   - uint16_t var_u16 ..: %3u @ 0x%X\n", var_u16, &var_u16);
  Serial.printf("   - int16_t  var_i16 ..: %3i @ 0x%X\n", var_i16, &var_i16);
  Serial.printf("   - uint32_t var_u32 ..: %3u @ 0x%X\n", var_u32, &var_u32);
  Serial.printf("   - int32_t  var_i32 ..: %3i @ 0x%X\n", var_i32, &var_i32);
  Serial.printf("   - float    var_flt ..: %1.1f @ 0x%X\n", var_flt, &var_flt);
  Serial.printf("   - double   var_dbl ..: %1.1f @ 0x%X\n", var_dbl, &var_dbl);

  Serial.printf(" - Indirect-access (using pointers):\n");
  Serial.printf("   - Pointed by pt_u8 ..: %3u @ 0x%X\n", *pt_u8, pt_u8);
  Serial.printf("   - Pointed by pt_i8 ..: %3i @ 0x%X\n", *pt_i8, pt_i8);
  Serial.printf("   - Pointed by pt_ch ..: %3c @ 0x%X\n", *pt_ch, pt_ch);

  /* Reassign pointers from single variables to arrays members */
  /* Same: pt_u8 = &arr_u8[0]; */
  pt_u8 = arr_u8;
  /* Same: pt_i8 = &arr_i8[0]; */
  pt_i8 = arr_i8;
  /* Same: pt_ch = &arr_ch[0]; */
  pt_ch = arr_ch;
  Serial.printf(" - Same pointers, but reassigned to arrays:\n");
  Serial.printf("   - Pointed by pt_u8 ..: %3u @ 0x%X\n", *pt_u8, pt_u8);
  Serial.printf("   - Pointed by pt_i8 ..: %3i @ 0x%X\n", *pt_i8, pt_i8);
  Serial.printf("   - Pointed by pt_ch ..: %3c @ 0x%X\n", *pt_ch, pt_ch);

  /* Move to next position on arrays */
  pt_u8++;
  pt_i8++;
  pt_ch++;
  Serial.printf(" - Same pointers, but after incrementing by 1:\n");
  Serial.printf("   - Pointed by pt_u8 ..: %3u @ 0x%X\n", *pt_u8, pt_u8);
  Serial.printf("   - Pointed by pt_i8 ..: %3i @ 0x%X\n", *pt_i8, pt_i8);
  Serial.printf("   - Pointed by pt_ch ..: %3c @ 0x%X\n", *pt_ch, pt_ch);

  /* ~~ o ~~ */

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
Ahoy! ESP8266 here!
---
Checking variables assignments:
(TIP: '@' means 'addressed at')
 - Direct-access (using variable name):
   - uint8_t  var_u8 ...:   8 @ 0x3FFFFF82
   - int8_t   var_i8 ...:  -8 @ 0x3FFFFF81
   - char     var_ch ...:   c @ 0x3FFFFF80
   - uint16_t var_u16 ..:  16 @ 0x3FFFFF7E
   - int16_t  var_i16 ..: -16 @ 0x3FFFFF7C
   - uint32_t var_u32 ..:  32 @ 0x3FFFFF78
   - int32_t  var_i32 ..: -32 @ 0x3FFFFF74
   - float    var_flt ..: 1.0 @ 0x3FFFFF70
   - double   var_dbl ..: 2.0 @ 0x3FFFFF68
 - Indirect-access (using pointers):
   - Pointed by pt_u8 ..:   8 @ 0x3FFFFF82
   - Pointed by pt_i8 ..:  -8 @ 0x3FFFFF81
   - Pointed by pt_ch ..:   c @ 0x3FFFFF80
 - Same pointers, but reassigned to arrays:
   - Pointed by pt_u8 ..:   1 @ 0x3FFFFF60
   - Pointed by pt_i8 ..:  -1 @ 0x3FFFFF58
   - Pointed by pt_ch ..:   a @ 0x3FFFFF50
 - Same pointers, but after incrementing by 1:
   - Pointed by pt_u8 ..:   2 @ 0x3FFFFF61
   - Pointed by pt_i8 ..:  -2 @ 0x3FFFFF59
   - Pointed by pt_ch ..:   b @ 0x3FFFFF51
Locking now
```

### Ejemplo 2: Mezclando signos y tipos

En este ejemplo se muestran todas las direcciones en forma de tabla y se accede a unos elementos interpretandolos de forma diferente al tipo que los define, a traves de su dirección (usando punteros).

Este ejemplo mostrará una información y se bloqueará. Para poder volver a verla hay que resetear la placa pulsando brevemente el botón de reset lateral.

```C
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

/*
 * Recurrent task, called forever
 */
void loop()
{
  /* Create a few arrays */
  uint8_t  arr_u8[8] = {  1,   2,   3,   4,   5,   6,   7,   8  };
  int8_t   arr_i8[8] = { -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8  };
  char     arr_ch[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

  /* 
   * Print a table of addresses
   */

  /* Helper variables */
  uint8_t idx0       = 0;
  Serial.printf("Address of each array member:\n");
  Serial.printf("\n");

  /* Table: Header */
  Serial.printf(" Type    ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| Index nr.%u ", idx0);
  }
  Serial.printf("\n");

  /* Table: Separator */
  Serial.printf("---------");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("+------------");
  }
  Serial.printf("\n");

  /* Table: uint8_t row */
  Serial.printf(" uint8_t ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_u8[idx0]);
  }
  Serial.printf("\n");
  
  /* Table: int8_t row */
  Serial.printf("  int8_t ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_i8[idx0]);
  }
  Serial.printf("\n");
  
  /* Table: char row */
  Serial.printf("    char ");
  for (idx0 = 0; idx0 < 8; idx0++)
  {
    Serial.printf("| 0x%08X ", &arr_ch[idx0]);
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
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
Address of each array member:

 Type    | Index nr.0 | Index nr.1 | Index nr.2 | Index nr.3 | Index nr.4 | Index nr.5 | Index nr.6 | Index nr.7 
---------+------------+------------+------------+------------+------------+------------+------------+------------
 uint8_t | 0x3FFFFF70 | 0x3FFFFF71 | 0x3FFFFF72 | 0x3FFFFF73 | 0x3FFFFF74 | 0x3FFFFF75 | 0x3FFFFF76 | 0x3FFFFF77 
  int8_t | 0x3FFFFF68 | 0x3FFFFF69 | 0x3FFFFF6A | 0x3FFFFF6B | 0x3FFFFF6C | 0x3FFFFF6D | 0x3FFFFF6E | 0x3FFFFF6F 
    char | 0x3FFFFF60 | 0x3FFFFF61 | 0x3FFFFF62 | 0x3FFFFF63 | 0x3FFFFF64 | 0x3FFFFF65 | 0x3FFFFF66 | 0x3FFFFF67 

Checking variables assignments:
 - Indirect-access (using pointers):
   - Pointed by pt_u8 ..:        8 [0x00000008]
   - Pointed by pt_i8 ..:       -8 [0xFFFFFFF8]
   - Pointed by pt_ch ..:        h [0x00000068]
 - A uint8_t reading data from a negative int8_t:
   - Pointed by pt_u8 ..:      248 [0x000000F8]
 - A uint32_t reading data from a negative int8_t:
   - Pointed by pt_u32 .: 50463224 [0x030201F8]
Locking now
```

### Ejemplo 3: Obviando tipos sabiendo el tamaño del dato

Este ejemplo es esencialmente el mismo que el anterior, solo que aplica una fórmula diferente para imprimir la tabla por pantalla.

Comparando ambos ejemplos, se ve como ocupan prácticamente las mismas lineas, por lo que puede parecer que no aporta nada la complejidad extra pero ... sólo hace falta agregar 1 o 2 lineas mas a la tabla para comenzar a ver la diferencia.

Básicamente, el ejemplo 2 es algo "estático" o "hardcodeado", y su mantenimiento será mas complicado en caso de necesitar modificarse. Este ejemplo sin embargo, permite adaptarse a los cambios de una forma rápida y eficiente.

Este ejemplo mostrará una información y se bloqueará. Para poder volver a verla hay que resetear la placa pulsando brevemente el botón de reset lateral.

```C
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
```

#### Salida esperada

```text
Ahoy! ESP8266 here!
---
Address of each array member:

| Index nr.0 | Index nr.1 | Index nr.2 | Index nr.3 | Index nr.4 | Index nr.5 | Index nr.6 | Index nr.7 
+------------+------------+------------+------------+------------+------------+------------+------------
| 0x3FFFFF78 | 0x3FFFFF79 | 0x3FFFFF7A | 0x3FFFFF7B | 0x3FFFFF7C | 0x3FFFFF7D | 0x3FFFFF7E | 0x3FFFFF7F 
| 0x3FFFFF70 | 0x3FFFFF71 | 0x3FFFFF72 | 0x3FFFFF73 | 0x3FFFFF74 | 0x3FFFFF75 | 0x3FFFFF76 | 0x3FFFFF77 
| 0x3FFFFF68 | 0x3FFFFF69 | 0x3FFFFF6A | 0x3FFFFF6B | 0x3FFFFF6C | 0x3FFFFF6D | 0x3FFFFF6E | 0x3FFFFF6F 


Checking variables assignments:
 - Indirect-access (using pointers):
   - Pointed by pt_u8 ..:        8 [0x00000008]
   - Pointed by pt_i8 ..:       -8 [0xFFFFFFF8]
   - Pointed by pt_ch ..:        h [0x00000068]
 - A uint8_t reading data from a negative int8_t:
   - Pointed by pt_u8 ..:      248 [0x000000F8]
 - A uint32_t reading data from a negative int8_t:
   - Pointed by pt_u32 .: 50463224 [0x030201F8]
Locking now
```
