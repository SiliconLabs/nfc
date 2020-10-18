/***************************************************************************//**
 * @file  main.c
 * @brief NT3H2x11 Tag memory read/dump example.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

/* ...
 *
 * EXPERIMENTAL QUALITY
 * This code has not been formally tested and is provided as-is.  It is not suitable for production environments.
 * This code will not be maintained.
 *
... */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "retargetserial.h"
#include "serial.h"
/* NT3H2X11 files. */
#include "nt3h2x11.h"

/* Define your board here */
#define BRD4162A 1

/* EFR32xG12 Boards*/
#if    (BRD4103A == 1)\
    || (BRD4161A == 1)\
    || (BRD4162A == 1)\
    || (BRD4163A == 1)\
    || (BRD4164A == 1)\
    || (BRD4170A == 1)\
    || (BRD4172A == 1)\
    || (BRD4172B == 1)\
    || (BRD4173A == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     11
#define NT3H2X11_I2C_SCL_PIN     10
#define NT3H2X11_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC16
#define NT3H2X11_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC14

#elif  (BRD4166A == 1)\
    || (BRD4304A == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     10
#define NT3H2X11_I2C_SCL_PIN     11
#define NT3H2X11_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC15
#define NT3H2X11_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC15

/* EFR32xG13 Boards*/
#elif  (BRD4104A == 1)\
    || (BRD4158A == 1)\
    || (BRD4159A == 1)\
    || (BRD4165B == 1)\
    || (BRD4167A == 1)\
    || (BRD4168A == 1)\
    || (BRD4174A == 1)\
    || (BRD4174B == 1)\
    || (BRD4175A == 1)\
    || (BRD4305A == 1)\
    || (BRD4305C == 1)\
    || (BRD4305D == 1)\
    || (BRD4305E == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     11
#define NT3H2X11_I2C_SCL_PIN     10
#define NT3H2X11_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC16
#define NT3H2X11_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC14

#elif  (BRD4306A == 1)\
    || (BRD4306B == 1)\
    || (BRD4306C == 1)\
    || (BRD4306D == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     10
#define NT3H2X11_I2C_SCL_PIN     11
#define NT3H2X11_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC15
#define NT3H2X11_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC15

/* EFR32xG21 Boards*/
#elif  (BRD4180A == 1)\
    || (BRD4180B == 1)\
    || (BRD4181A == 1)\
    || (BRD4181B == 1)\
    || (BRD4181C == 1)\
    || (BRD4308A == 1)\
    || (BRD4308B == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     2
#define NT3H2X11_I2C_SCL_PIN     3

#elif (BRD4309B == 1)

#warning "Limited pins on BRD4309B, VCOM can not be used when using this board with I2C."

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortC
#define NT3H2X11_I2C_SCL_PORT    gpioPortC
#define NT3H2X11_I2C_SDA_PIN     0
#define NT3H2X11_I2C_SCL_PIN     1

/* EFR32xG22 Boards*/
#elif  (BRD4182A == 1)\
    || (BRD4310A == 1)\
    || (BRD4311A == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortB
#define NT3H2X11_I2C_SCL_PORT    gpioPortB
#define NT3H2X11_I2C_SDA_PIN     3
#define NT3H2X11_I2C_SCL_PIN     2

#elif  (BRD4183A == 1)

#warning "Limited pins on BRD4183A, VCOM can not be used when using this board with I2C."

#define NT3H2X11_I2C             I2C0

#define NT3H2X11_I2C_SDA_PORT    gpioPortA
#define NT3H2X11_I2C_SCL_PORT    gpioPortA
#define NT3H2X11_I2C_SDA_PIN     5
#define NT3H2X11_I2C_SCL_PIN     6

#elif  (BRD4184A == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortD
#define NT3H2X11_I2C_SCL_PORT    gpioPortD
#define NT3H2X11_I2C_SDA_PIN     2
#define NT3H2X11_I2C_SCL_PIN     3

#elif  (BRD4314A == 1)

#define NT3H2X11_I2C             I2C0
#define NT3H2X11_I2C_SDA_PORT    gpioPortD
#define NT3H2X11_I2C_SCL_PORT    gpioPortD
#define NT3H2X11_I2C_SDA_PIN     3
#define NT3H2X11_I2C_SCL_PIN     2

#else

// Custom board
#define NT3H2X11_I2C
#define NT3H2X11_I2C_SDA_PORT
#define NT3H2X11_I2C_SCL_PORT
#define NT3H2X11_I2C_SDA_PIN
#define NT3H2X11_I2C_SCL_PIN

#endif

#if (_SILICON_LABS_32B_SERIES == 1)
#define NT3H2X11_I2C_INIT_DEFAULT {                           \
    true,                        /* Enable */                 \
    NT3H2X11_I2C,                /* Use I2C instance 0 */     \
    NT3H2X11_I2C_SCL_PORT,       /* SCL port */               \
    NT3H2X11_I2C_SCL_PIN,        /* SCL pin */                \
    NT3H2X11_I2C_SDA_PORT,       /* SDA port */               \
    NT3H2X11_I2C_SDA_PIN,        /* SDA pin */                \
    NT3H2X11_I2C_SCL_LOC,        /* SCL Location */           \
    NT3H2X11_I2C_SDA_LOC,        /* SDA Location  */          \
}
#elif (_SILICON_LABS_32B_SERIES == 2)
#define NT3H2X11_I2C_INIT_DEFAULT {                           \
    true,                        /* Enable */                 \
    NT3H2X11_I2C,                /* Use I2C instance 0 */     \
    NT3H2X11_I2C_SCL_PORT,       /* SCL port */               \
    NT3H2X11_I2C_SCL_PIN,        /* SCL pin */                \
    NT3H2X11_I2C_SDA_PORT,       /* SDA port */               \
    NT3H2X11_I2C_SDA_PIN,        /* SDA pin */                \
}
#endif

nt3h2x11_init_t nt3h2x11_init_only_i2c = {
    .i2c_init = NT3H2X11_I2C_INIT_DEFAULT,
    .fd_init = { .enable = false }
};

/* Buffer array to hold memory data. */
uint8_t data0[16] = {0};
uint8_t data1[16] = {0};
uint8_t data2[16] = {0};
uint8_t data3[16] = {0};

/* Main function */
int main(void)
{
  // Device errata
  CHIP_Init();
  // Enable GPIO clock source
  CMU_ClockEnable(cmuClock_GPIO, true);
  // Enable VCOM
  GPIO_PinModeSet(BSP_BCC_ENABLE_PORT, BSP_BCC_ENABLE_PIN, gpioModePushPull, 1);
  /* Initialize NT3H2x11 I2C communication. */
  nt3h2x11_init(nt3h2x11_init_only_i2c);
  /* Initialize STK serial output. */
  RETARGET_SerialInit();
  /* Print project name. */
  printf("\r\nNT3H2X11 Memory Dump.\r\n");

  /* Dump memory. */
  for (int i = 0; i < 64; i++) {
    /* skip memory bock 128 to 247 for both 1k and 2k version of NT3H2x11. */
    if ( (i >= 32) && (i < 62) ) {
      continue;
    }
    /* Read 4 memory blocks. */
    i2c_transfer_return_t i2c_read_result1 = nt3h2x11_read_block(4 * i, data0);
    i2c_transfer_return_t i2c_read_result2 = nt3h2x11_read_block(4 * i + 1, data1);
    i2c_transfer_return_t i2c_read_result3 = nt3h2x11_read_block(4 * i + 2, data2);
    i2c_transfer_return_t i2c_read_result4 = nt3h2x11_read_block(4 * i + 3, data3);

    /* Print first 4 bytes of block (4 * i). */
    printf("Block %3d: ", 4 * i);
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data0[0], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print first 4 bytes of block (4 * i + 1). */
    printf("     Block %3d: ", 4 * i + 1);
    if (i2c_read_result2 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data1[0], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print first 4 bytes of block (4 * i + 2). */
    printf("     Block %3d: ", 4 * i + 2);
    if (i2c_read_result3 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data2[0], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print first 4 bytes of block (4 * i + 3). */
    printf("     Block %3d: ", 4 * i + 3);
    if (i2c_read_result4 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data3[0], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* New line. */
    printf("\r\n");

    /* Print second 4 bytes of block (4 * i). */
    printf("           ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data0[4], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print second 4 bytes of block (4 * i + 1). */
    printf("                ");
    if (i2c_read_result2 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data1[4], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print second 4 bytes of block (4 * i + 2). */
    printf("                ");
    if (i2c_read_result3 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data2[4], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print second 4 bytes of block (4 * i + 3). */
    printf("                ");
    if (i2c_read_result4 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data3[4], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* New line. */
    printf("\r\n");

    /* Print third 4 bytes of block (4 * i). */
    printf("           ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data0[8], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print third 4 bytes of block (4 * i + 1). */
    printf("                ");
    if (i2c_read_result2 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data1[8], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print third 4 bytes of block (4 * i + 2). */
    printf("                ");
    if (i2c_read_result3 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data2[8], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print third 4 bytes of block (4 * i + 3). */
    printf("                ");
    if (i2c_read_result4 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data3[8], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* New line. */
    printf("\r\n");

    /* Print last 4 bytes of block (4 * i). */
    printf("           ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data0[12], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print last 4 bytes of block (4 * i + 1). */
    printf("                ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data1[12], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print last 4 bytes of block (4 * i + 2). */
    printf("                ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data2[12], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* Print last 4 bytes of block (4 * i + 3). */
    printf("                ");
    if (i2c_read_result1 == i2cTransferDone) {
      serial_put_hex_and_ascii(&data3[12], 4);
    } else {
      printf(" -- -- -- --    ----");
    }
    /* New line. */
    printf("\r\n");

  }

  return 0;
}
