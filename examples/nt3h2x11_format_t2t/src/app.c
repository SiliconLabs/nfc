/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* ...
 *
 * EXPERIMENTAL QUALITY
 * This code has not been formally tested and is provided as-is.  It is not suitable for production environments.
 * This code will not be maintained.
 *
... */

#include <stdio.h>
#include <string.h>
#include "sl_iostream.h"
#include "t2t.h"
#include "nt3h2x11.h"

/* Define your board here */
#define BRD4314A 1

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

/*  T2T_Area_Size = (T2T_CC2_SIZE * 8) */
#define T2T_CC2_SIZE      0x6D

nt3h2x11_init_t nt3h2x11_init_only_i2c = {
    .i2c_init = NT3H2X11_I2C_INIT_DEFAULT,
    .fd_init = { .enable = false }
};

uint8_t block0_data[] = {
    /* Byte 0 needs to be I2C address as writing to
     * it changes the I2C address.
     * See NT3H2111_2211 data sheet section 9.6 for details. */
    NT3H2X11_DEFAULT_I2C_ADDR, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    /* Byte 10 - 11 are the static lock bits, writing
     * 1 to them would permanently lock some memory area.
     * See NT3H2111_2211 data sheet section 8.3.6 for details. */
    0x00, 0x00, 0x00, 0x00,
    /* Byte 12 to 15 are the CC, format as following to make it T2T compatible.
     * Byte 12 - Magic Number (0xE1) indicates this is a T2T.
     * Byte 13 - T2T mapping version.
     * Byte 14 - sets T2T_Area Size, T2T_Area_Size = T2T_CC2_SIZE * 8. Set it accordingly for your need.
     * Byte 15 - the access condition.
     * See NT3H2111_2211 data sheet section 8.3.8 for details.*/
    T2T_CC0, T2T_CC1_VERSION_1_0, T2T_CC2_SIZE, 0x00
};

sl_iostream_t *default_iostream;

uint16_t read_cc2_size (void) {

  char char_buff;
  size_t bytes_read;
  uint16_t size_digits[3];
  uint8_t size_len = 0;

  while(1) {
      sl_iostream_read (default_iostream, &char_buff, 1, &bytes_read);

      if (bytes_read > 0) {
          if ((char_buff >= '0') && (char_buff <= '9')) {
              if (size_len < 3) {
                  size_digits[size_len] = char_buff - '0';
                  size_len++;
                  printf("%c", char_buff);
              }
              else {
                  printf("\r\nInvalid block number: too many digits. Please input a number between 0 and 255, press ENTER when you finish: ");
                  size_len = 0;
              }
          }
          else if (char_buff == '\r') {
              if (size_len == 0) {
                  printf("\r\nPlease input a number between 0 and 255, press ENTER when you finish: ");
                  continue;
              }
              printf("\r\n");
              break;
          }
          else {
              printf("\r\nInvalid character. Please input a number between 0 and 255, press ENTER when you finish: ");
              size_len = 0;
          }
      }
  }

  uint16_t size_read = 0;

  if (size_len == 1) {
      size_read = size_digits[0];
  }
  else if (size_len == 2) {
      size_read = size_digits[0] * 10 + size_digits[1];
  }
  else if (size_len == 3) {
      size_read = size_digits[0] * 100 + size_digits[1] * 10 + size_digits[2];
  }
  return size_read;
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
  /* Initialize NT3H2x11 I2C communication. */
  nt3h2x11_init(nt3h2x11_init_only_i2c);
  default_iostream = sl_iostream_get_default();
  /* Print project name. */
  printf("\r\n******************************\r\n*\r\n");
  printf("* NT3H2X11 T2T Format via I2C\r\n");
  printf("*\r\n******************************\r\n");
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {

  uint16_t cc2_size = 0;

  do {
      printf("\r\nGive a T2T CC2 Size, where T2T_Area_Size = CC2_Size * 8, your input should be between 6 and 255, press enter when you finish: ");
      cc2_size = read_cc2_size();
      if (((cc2_size < 6) || (cc2_size > 255))) {
          printf("Your input should be between 6 and 255.\r\n");
      }
  } while ((cc2_size < 6) || (cc2_size > 255));

  block0_data[14] = cc2_size;

  /* Write to NT3H2x11 block 0. */
  while (nt3h2x11_write_block(0, block0_data) != i2cTransferDone);

  printf("Format completed.\r\n");

}
