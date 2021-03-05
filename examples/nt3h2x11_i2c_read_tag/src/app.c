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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "serial.h"
#include "sl_iostream.h"
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

nt3h2x11_init_t nt3h2x11_init_only_i2c = {
    .i2c_init = NT3H2X11_I2C_INIT_DEFAULT,
    .fd_init = { .enable = false }
};

uint8_t data_buff[4][16];
i2c_transfer_return_t i2c_read_results[4];

sl_iostream_t *default_iostream;

static bool blk_addrs_received = false;

uint16_t read_blk_addr (void) {
  
  char char_buff;
  size_t bytes_read;
  uint16_t blk_addr_digits[3];
  uint8_t blk_addr_len = 0;
  
  while(1) {
      sl_iostream_read (default_iostream, &char_buff, 1, &bytes_read);
      
      if (bytes_read > 0) {
          if ((char_buff >= '0') && (char_buff <= '9')) {
              if (blk_addr_len < 3) {
                  blk_addr_digits[blk_addr_len] = char_buff - '0';
                  blk_addr_len++;
                  printf("%c", char_buff);
              }
              else {
                  printf("\r\nInvalid block number: too many digits. Please input a number between 0 and 255, press ENTER when you finish: ");
                  blk_addr_len = 0;
              }
          }
          else if (char_buff == '\r') {
              if (blk_addr_len == 0) {
                  printf("\r\nPlease input a number between 0 and 255, press ENTER when you finish: ");
                  continue;
              }
              printf("\r\n");
              break;
          }
          else {
              printf("\r\nInvalid character. Please input a number between 0 and 255, press ENTER when you finish: ");
              blk_addr_len = 0;
          }
      }
  }
  
  uint16_t addr_read = 0;
  
  if (blk_addr_len == 1) {
      addr_read = blk_addr_digits[0];
  }
  else if (blk_addr_len == 2) {
      addr_read = blk_addr_digits[0] * 10 + blk_addr_digits[1];
  }
  else if (blk_addr_len == 3) {
      addr_read = blk_addr_digits[0] * 100 + blk_addr_digits[1] * 10  + blk_addr_digits[2];
  }
  return addr_read;
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
  printf("* NT3H2X11 Memory Dump\r\n");
  printf("*\r\n******************************\r\n");
  
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {
  
  uint16_t start_blk_addr = 0;
  uint16_t end_blk_addr = 0;
  
  do {
      printf("\r\nGive a start block address between 0 and 255, press ENTER when you finish: ");
      start_blk_addr = read_blk_addr();
      if (start_blk_addr > 255) {
          printf("Start block address should be between 0 and 255. \r\n");
      }
  } while (start_blk_addr > 255);
  
  do {
      printf("Give an ending block address between %d and 255, press ENTER when you finish: ", start_blk_addr);
      end_blk_addr = read_blk_addr();
      if ((end_blk_addr < start_blk_addr) || (end_blk_addr > 255)) {
          printf("End block address should be between %d and 255. \r\n", start_blk_addr);
      }
  } while (end_blk_addr < start_blk_addr || (end_blk_addr > 255));
  
  printf("\r\nStart block address: %d, ", start_blk_addr);
  printf("End block address: %d\r\n\r\n", end_blk_addr);
  
  blk_addrs_received = true;
  
  if (blk_addrs_received) {
      /* Dump memory. */
      for(int i = start_blk_addr; i <= end_blk_addr;) {
          
          int j;
          
          for(j = 0; (j < 4) && (i <= end_blk_addr); j++) {
              i2c_read_results[j] = nt3h2x11_read_block(i++, data_buff[j]);
          }
          
          for(int k = 0; k < j; k++) {
              if (k > 0) {
                  printf("     ");
              }
              printf("Block %3d: ", i - j + k);
              if (i2c_read_results[k] == i2cTransferDone) {
                  serial_put_hex_and_ascii(&data_buff[k][0], 4);
              }
              else {
                  printf(" -- -- -- --    ----");
              }
          }
          
          /* New line. */
          printf("\r\n");
          
          for(int k = 0; k < j; k++) {
              if (k > 0)  {
                  printf("     ");
              }
              printf("           ");
              if (i2c_read_results[k] == i2cTransferDone) {
                  serial_put_hex_and_ascii(&data_buff[k][4], 4);
              }
              else {
                  printf(" -- -- -- --    ----");
              }
          }
          
          /* New line. */
          printf("\r\n");
          
          for(int k = 0; k < j; k++) {
              if (k > 0) {
                  printf("     ");
              }
              printf("           ");
              if (i2c_read_results[k] == i2cTransferDone) {
                  serial_put_hex_and_ascii(&data_buff[k][8], 4);
              }
              else {
                  printf(" -- -- -- --    ----");
              }
          }
          
          /* New line. */
          printf("\r\n");
          
          for(int k = 0; k < j; k++) {
              if (k > 0) {
                  printf("     ");
              }
              printf("           ");
              if (i2c_read_results[k] == i2cTransferDone) {
                  serial_put_hex_and_ascii(&data_buff[k][12], 4);
              }
              else {
                  printf(" -- -- -- --    ----");
              }
          }
          
          /* New line. */
          printf("\r\n");
          
          blk_addrs_received = false;
        }
    }
}
