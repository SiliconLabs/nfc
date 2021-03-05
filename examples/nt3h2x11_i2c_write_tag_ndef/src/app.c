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
#include "nt3h2x11.h"
#include "ndef_message.h"
#include "tlv.h"
#include "t2t.h"

/* Define your board here */
//#define BRD4162A 1
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

#define TLV_BUFFER_SIZE             100
#define PAYLOAD_BUFFER_SIZE         100

nt3h2x11_init_t nt3h2x11_init_only_i2c = {
    .i2c_init = NT3H2X11_I2C_INIT_DEFAULT,
    .fd_init = { .enable = false }
};

sl_iostream_t *default_iostream;

/* Buffer to hold NFEF record payload. */
uint8_t payload_buff[PAYLOAD_BUFFER_SIZE];
/* NDEF record container to fill up. */
ndef_record_t record = {
    .header = {
        .mb  = 1,
        .me  = 1,
        .cf  = 0,
        .sr  = 1,
        .il  = 0,
        .tnf = ndefTnfWellKnown
    },
    .type_length = 1,
    .type = (uint8_t*) NDEF_RTD_WKT_GLOBAL_URI
};
/* NDEF message with 1 record. */
ndef_record_t ndef_message[1];
/* Buffer to hold encoded NDEF message raw data. */
uint8_t ndef_message_buff[TLV_BUFFER_SIZE - 3];
/* Buffer to hold encoded TLV raw data. */
uint8_t tlv_buff[TLV_BUFFER_SIZE];
/* Content to be written into NDEF payload. */
char* default_url = "silabs.com/wireless/bluetooth";
char custom_url[100];
uint8_t custom_url_len;

static bool first_run = true;

void read_url (void) {

  char char_buff;
  size_t bytes_read;
  custom_url_len = 0;

  while(1) {
      sl_iostream_read (default_iostream, &char_buff, 1, &bytes_read);

      if (bytes_read > 0) {

          if (char_buff == '\r') {
              if (custom_url_len == 0) {
                  printf("\r\nPlease give an URL, press ENTER when you finish: ");
                  continue;
              }
              printf("\r\n");
              break;
          }
          custom_url[custom_url_len++] = char_buff;
          printf("%c", char_buff);
      }
  }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
  /* Initialize NT3H2x11 I2C communication. */
  nt3h2x11_init(nt3h2x11_init_only_i2c);

  default_iostream = sl_iostream_get_default();
  /* Print project name. */
  printf("\r\n****************************************\r\n*\r\n");
  printf("* NT3H2x11 NDEF message write via I2C\r\n");
  printf("*\r\n***************************************\r\n");
  /* Assign pointer to payload buffer to the record payload. */
  record.payload = payload_buff;
  /* Payload length = length of prefix + length of content */
  record.payload_length = 1 + strlen(default_url);
  /* Add record to NDEF message. */
  ndef_message[0] = record;
  /* Add HTTPS prefix. */
  record.payload[0] = NDEF_RTD_WKT_URI_PREFIX_HTTPS;
  /* Copy content into payload. */
  memcpy(&record.payload[1], default_url, strlen(default_url));
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {

  if (!first_run) {

      printf("Give your custom URL, press ENTER to finish: ");

      read_url();

      /* Payload length = length of prefix + length of content */
      record.payload_length = 1 + custom_url_len;
      /* Add record to NDEF message. */
      ndef_message[0] = record;
      /* Copy content into payload. */
      memcpy(&record.payload[1], custom_url, custom_url_len);
  }
  /* Encode ndef message. */
  ndef_message_encode_result_t ndef_message_encode_result;
  ndef_message_encode_result = ndef_message_encode(ndef_message_buff, ndef_message);
  /* Check NDEF message encode result. */
  if ( ndef_message_encode_result.err == ndefMessageEncodeFail ) {
      printf("NDEF message encode failed:(\r\n");
      return;
  }

  /* Save bytes encoded into write size */
  int write_size = ndef_message_encode_result.size;

  /* Encode ndef TLV. */
  if (tlv_encode(tlv_buff,
                 TLV_BUFFER_SIZE,
                 NFC_T2T_NDEF_MESSAGE_TLV,
                 ndef_message_encode_result.size,
                 ndef_message_buff
  ) != tlvEncodeCompleted ) {
      printf("NDEF TLV encode failed:(\r\n");
      return;
  }
  /* Increment write size by 2 bytes (type, length). */
  write_size += 2;

  /* Encode terminator TLV (append to the end of NDEF TLV). */
  if ( tlv_encode(&tlv_buff[write_size],
                  (TLV_BUFFER_SIZE - write_size),
                  NFC_T2T_TERMINATOR_TLV,
                  0,
                  NULL
  )!= tlvEncodeCompleted ) {
      printf("Terminator TLV encode failed:(\r\n");
      return;
  }
  /* Increment write size by 1 byte (terminator type). */
  write_size++;
  /* Write to NT3H2x11. */
  for (int i = 1; (i - 1) * 16 <= write_size; i++) {
      while (nt3h2x11_write_block(i, &tlv_buff[(i - 1) * 16]) != i2cTransferDone);
  }

  if (first_run) {
      printf("Default URL, silabs.com/wireless/bluetooth, has been written. \r\n");
      first_run = false;
  } else {
      printf("Your custom URL has been written. \r\n");
  }
}
