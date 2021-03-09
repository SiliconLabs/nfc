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
#include <string.h>
#include <stdio.h>
#include "em_core.h"
#include "ndef_message.h"
#include "t2t.h"
#include "tlv.h"
#include "nci.h"
#include "pn71x0.h"

/* Define your board here */
#define BRD4314A 1
//#define BRD4162A 1

/* EFR32xG12 Boards*/
#if    (BRD4103A == 1)\
    || (BRD4161A == 1)\
    || (BRD4162A == 1)\
    || (BRD4163A == 1)\
    || (BRD4164A == 1)\
    || (BRD4170A == 1)\

#define PN71x0_VEN_PORT  gpioPortD
#define PN71x0_VEN_PIN   (12)
#define PN71x0_IRQ_PORT  gpioPortC
#define PN71x0_IRQ_PIN   (9)

#elif  (BRD4166A == 1)

#define PN71x0_VEN_PORT  gpioPortF
#define PN71x0_VEN_PIN   (5)
#define PN71x0_IRQ_PORT  gpioPortF
#define PN71x0_IRQ_PIN   (6)

#elif  (BRD4172A == 1)\
    || (BRD4172B == 1)\
    || (BRD4173A == 1)\

#define PN71x0_VEN_PORT  gpioPortF
#define PN71x0_VEN_PIN   (4)
#define PN71x0_IRQ_PORT  gpioPortF
#define PN71x0_IRQ_PIN   (3)

#elif  (BRD4304A == 1)

#define PN71x0_VEN_PORT  gpioPortF
#define PN71x0_VEN_PIN   (5)
#define PN71x0_IRQ_PORT  gpioPortF
#define PN71x0_IRQ_PIN   (3)

/* EFR32xG13 Boards*/
#elif  (BRD4104A == 1)\
    || (BRD4159A == 1)\
    || (BRD4165B == 1)\
    || (BRD4168A == 1)\
    || (BRD4305A == 1)\
    || (BRD4305C == 1)\
    || (BRD4305D == 1)\
    || (BRD4305E == 1)\

#define PN71x0_VEN_PORT  gpioPortD
#define PN71x0_VEN_PIN   (12)
#define PN71x0_IRQ_PORT  gpioPortF
#define PN71x0_IRQ_PIN   (3)

#elif  (BRD4306A == 1)\
    || (BRD4306B == 1)\
    || (BRD4306C == 1)\
    || (BRD4306D == 1)\

#define PN71x0_VEN_PORT  gpioPortF
#define PN71x0_VEN_PIN   (5)
#define PN71x0_IRQ_PORT  gpioPortF
#define PN71x0_IRQ_PIN   (3)

/* EFR32xG21 Boards*/

#elif  (BRD4180A == 1)\
    || (BRD4181A == 1)

#define PN71x0_VEN_PORT  gpioPortB
#define PN71x0_VEN_PIN   (0)
#define PN71x0_IRQ_PORT  gpioPortB
#define PN71x0_IRQ_PIN   (1)

#elif  (BRD4180B == 1)\
    || (BRD4181B == 1)\
    || (BRD4181C == 1)

#define PN71x0_VEN_PORT  gpioPortD
#define PN71x0_VEN_PIN   (2)
#define PN71x0_IRQ_PORT  gpioPortD
#define PN71x0_IRQ_PIN   (3)

/* EFR32xG22 Boards*/
#elif  (BRD4182A == 1)

#define PN71x0_VEN_PORT  gpioPortD
#define PN71x0_VEN_PIN   (2)
#define PN71x0_IRQ_PORT  gpioPortD
#define PN71x0_IRQ_PIN   (3)

#elif  (BRD4184A == 1)

#define PN71x0_VEN_PORT  gpioPortD
#define PN71x0_VEN_PIN   (0)
#define PN71x0_IRQ_PORT  gpioPortD
#define PN71x0_IRQ_PIN   (1)

#elif  (BRD4314A == 1)

#define PN71x0_VEN_PORT  gpioPortC
#define PN71x0_VEN_PIN   (6)
#define PN71x0_IRQ_PORT  gpioPortB
#define PN71x0_IRQ_PIN   (3)

#endif


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

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortC
#define PN71X0_I2C_SCL_PORT    gpioPortC
#define PN71X0_I2C_SDA_PIN     11
#define PN71X0_I2C_SCL_PIN     10
#define PN71X0_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC16
#define PN71X0_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC14

#elif  (BRD4166A == 1)\
    || (BRD4304A == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortC
#define PN71X0_I2C_SCL_PORT    gpioPortC
#define PN71X0_I2C_SDA_PIN     10
#define PN71X0_I2C_SCL_PIN     11
#define PN71X0_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC15
#define PN71X0_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC15

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

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortC
#define PN71X0_I2C_SCL_PORT    gpioPortC
#define PN71X0_I2C_SDA_PIN     11
#define PN71X0_I2C_SCL_PIN     10
#define PN71X0_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC16
#define PN71X0_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC14

#elif  (BRD4306A == 1)\
    || (BRD4306B == 1)\
    || (BRD4306C == 1)\
    || (BRD4306D == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortC
#define PN71X0_I2C_SCL_PORT    gpioPortC
#define PN71X0_I2C_SDA_PIN     10
#define PN71X0_I2C_SCL_PIN     11
#define PN71X0_I2C_SDA_LOC     _I2C_ROUTELOC0_SDALOC_LOC15
#define PN71X0_I2C_SCL_LOC     _I2C_ROUTELOC0_SCLLOC_LOC15

/* EFR32xG21 Boards*/
#elif  (BRD4180A == 1)\
    || (BRD4180B == 1)\
    || (BRD4181A == 1)\
    || (BRD4181B == 1)\
    || (BRD4181C == 1)\
    || (BRD4308A == 1)\
    || (BRD4308B == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortC
#define PN71X0_I2C_SCL_PORT    gpioPortC
#define PN71X0_I2C_SDA_PIN     2
#define PN71X0_I2C_SCL_PIN     3

/* EFR32xG22 Boards*/
#elif  (BRD4182A == 1)\
    || (BRD4310A == 1)\
    || (BRD4311A == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortB
#define PN71X0_I2C_SCL_PORT    gpioPortB
#define PN71X0_I2C_SDA_PIN     3
#define PN71X0_I2C_SCL_PIN     2

#elif  (BRD4184A == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortD
#define PN71X0_I2C_SCL_PORT    gpioPortD
#define PN71X0_I2C_SDA_PIN     2
#define PN71X0_I2C_SCL_PIN     3

#elif  (BRD4314A == 1)

#define PN71X0_I2C             I2C0
#define PN71X0_I2C_SDA_PORT    gpioPortD
#define PN71X0_I2C_SCL_PORT    gpioPortD
#define PN71X0_I2C_SDA_PIN     3
#define PN71X0_I2C_SCL_PIN     2

#else

// Custom board
#define PN71X0_I2C
#define PN71X0_I2C_SDA_PORT
#define PN71X0_I2C_SCL_PORT
#define PN71X0_I2C_SDA_PIN
#define PN71X0_I2C_SCL_PIN

#endif

#if (_SILICON_LABS_32B_SERIES == 1)
#define PN71X0_I2C_INIT_DEFAULT {                           \
    PN71X0_I2C,                /* Use I2C instance 0 */     \
    PN71X0_I2C_SCL_PORT,       /* SCL port           */     \
    PN71X0_I2C_SCL_PIN,        /* SCL pin            */     \
    PN71X0_I2C_SDA_PORT,       /* SDA port           */     \
    PN71X0_I2C_SDA_PIN,        /* SDA pin            */     \
    PN71X0_I2C_SCL_LOC,        /* SCL Location       */     \
    PN71X0_I2C_SDA_LOC,        /* SDA Location       */     \
}
#elif (_SILICON_LABS_32B_SERIES == 2)
#define PN71X0_I2C_INIT_DEFAULT {                           \
    PN71X0_I2C,                /* Use I2C instance 0 */     \
    PN71X0_I2C_SCL_PORT,       /* SCL port */               \
    PN71X0_I2C_SCL_PIN,        /* SCL pin  */               \
    PN71X0_I2C_SDA_PORT,       /* SDA port */               \
    PN71X0_I2C_SDA_PIN,        /* SDA pin  */               \
}
#endif

#define PN71X0_GPIO_INIT_DEFAULT {                          \
    PN71x0_VEN_PORT,           /* VEN port */               \
    PN71x0_VEN_PIN,            /* VEN pin  */               \
    PN71x0_IRQ_PORT,           /* IRQ port */               \
    PN71x0_IRQ_PIN,            /* IRQ pin  */               \
}

pn71x0_init_t init = {
    .i2c_init  = PN71X0_I2C_INIT_DEFAULT,
    .gpio_init = PN71X0_GPIO_INIT_DEFAULT
};

/*
 * T2T Write Process
 * ---------------------------------------------------------------------------------------------------------------------
 * ----- Preparation Sequence ------
 * DH --> Core Reset CMD                                                                                        --> NFCC
 * DH <-- Core Reset RSP                                                                                        <-- NFCC
 * DH --> Core Init CMD                                                                                         --> NFCC
 * DH <-- Core Init RSP                                                                                         <-- NFCC
 * DH --> NXP Proprietary Act CMD                                                                               --> NFCC
 * DH <-- NXP Proprietary Act RSP                                                                               <-- NFCC
 * ----- RF Discover Phase ------
 * DH --> RF Discover Map CMD (RF Prot. = PROTOCOL_T2T, Mode = Poll, RF Intf. = Frame RF)                       --> NFCC
 * DH <-- RF Discover Map RSP                                                                                   <-- NFCC
 * DH --> RF Discover CMD (NFC_A_PASSIVE_POLL_MODE)                                                             --> NFCC
 * DH <-- RF Discover RSP                                                                                       <-- NFCC
 * DH <-- RF Intf Activated NTF (Prot = PROTOCOL_T2T, Intf = Frame RF)                                          <-- NFCC
 * ----- Data Exhange Phase (REPEAT) ------
 * DH --> NCI Data Message (WRITE Command, Block Address, Data)                                                 <-- NFCC
 * DH <-- Core Conn Credits NTF                                                                                 <-- NFCC
 * DH <-- NCI Data Message (ACK or NACK Response)                                                               <-- NFCC
 * ----- RF Deactivate Phase ------
 * DH --> RF Deactivate CMD (Discovery)                                                                         <-- NFCC
 * DH <-- RF Deactivate RSP                                                                                     <-- NFCC
 * DH --> RF Deactivate NTF                                                                                     <-- NFCC
 * ----- Go Back to RF Discover Phase ------
 */

#define TLV_BUFFER_SIZE             100
#define PAYLOAD_BUFFER_SIZE         100

char* content = "silabs.com/wireless/bluetooth";
uint8_t payload[PAYLOAD_BUFFER_SIZE];

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

ndef_record_t ndef_message[1];

uint8_t ndef_message_buff[TLV_BUFFER_SIZE - 3];
uint8_t tlv_buff[TLV_BUFFER_SIZE];

//    uint8_t conn_credits = 0;
uint16_t write_index = 0;
uint32_t write_size;

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  /* Initialize PN71x0 I2C communication. */
   pn71x0_init(init);
   /* Initialize NCI. */
   nci_init();

   /* Print project name. */
   printf("\r\n******************************\r\n*\r\n");
   printf("* NCI T2T Write Demo\r\n");
   printf("*\r\n******************************\r\n");

   printf("Write content: %s\r\n", content);

   record.payload = payload;
   // prefix + content
   record.payload_length = 1 + strlen(content);

   ndef_message[0] = record;

   payload[0] = NDEF_RTD_WKT_URI_PREFIX_HTTPS;

   memcpy(&payload[1], content, strlen(content));

   // encode ndef message
   ndef_message_encode_result_t ndef_message_encode_result;
   ndef_message_encode_result = ndef_message_encode(ndef_message_buff, ndef_message);
   if ( ndef_message_encode_result.err == ndefMessageEncodeFail ) {
       printf("NDEF message encode failed:(\r\n");
       return;
   }

   write_size = ndef_message_encode_result.size;

   // encode ndef tlv
   if (tlv_encode(tlv_buff,
                  TLV_BUFFER_SIZE,
                  NFC_T2T_NDEF_MESSAGE_TLV,           // T
                  ndef_message_encode_result.size,    // L
                  ndef_message_buff                   // V
   ) != tlvEncodeCompleted ) {
       printf("NDEF TLV encode failed:(\r\n");
       return;
   }

   write_size += 2;

   if ( tlv_encode(&tlv_buff[write_size],
                   (TLV_BUFFER_SIZE - write_size),
                   NFC_T2T_TERMINATOR_TLV,       // T
                   0,                            // L
                   NULL                          // V
   )!= tlvEncodeCompleted ) {
       printf("Terminator TLV encode failed:(\r\n");
       return;
   }

   write_size++;
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
  /* Get NCI event. */
  nci_evt_t* nci_evt = nci_get_event();

  if(nci_evt->header == nci_evt_none) {
      return;
  }

  /* Log NCI event, if debug enabled. */
  nci_evt_log (nci_evt->header);

  switch (nci_evt->header) {
    /* Start up event, enter init sequence. */
    case nci_evt_startup: {
      /* Step 1 in init sequence: core reset. */
      nci_core_reset_cmd_t core_reset_cmd;
      /* Keep configurations. */
      core_reset_cmd.reset_type = nci_core_reset_keep_config;
      /* Send command and check for error/ */
      if (nci_core_reset(&core_reset_cmd) != nci_err_none) {
          printf("NCI core reset error. \r\n");
          return;
      }
      break;
    }
    /* Event generated by reception of core reset response. */
    case nci_evt_core_reset_rsp_rec: {
      /* Get core reset response data: NCI version of NFCC. */
      uint8_t nci_version = nci_evt->data.payload.nci_data.core_reset_rsp.nci_version;
      /* Get core reset response data: configuration status. */
      uint8_t config_status = nci_evt->data.payload.nci_data.core_reset_rsp.config_status;
      /* Log NCI version of NFCC. */
      printf("NFCC's NCI Version is %x.%x\r\n", ((nci_version & 0xF0) >> 4), (nci_version & 0x0F));
      /* Log configuration status. */
      if (config_status == nci_core_reset_keep_config) {
          nci_log_ln("NCI RF Configuration has been kept.");
      }
      else if (config_status == nci_core_reset_reset_conig) {
          nci_log_ln("NCI RF Configuration has been reset. ");
      }
      /* Step 2 in init sequence: core init. */
      /* Send command and check for error. */
      if (nci_core_init() != nci_err_none) {
          printf("NCI core init error. \r\n");
          return;
      }
      break;
    }
    /* Event generated by reception of core init response. */
    case nci_evt_core_init_rsp_rec: {

      uint8_t* manu_spec_info = nci_evt->data.payload.nci_data.core_init_rsp.manu_spec_info;

      printf("NFCC's Firmware Version is %02x.%02x\r\n", manu_spec_info[2], manu_spec_info[3]);
      /* Activate NXP proprietary extensions, send command and check for error. */
      if (nci_proprietary_nxp_act() != nci_err_none) {
          printf("NCI core init error. \r\n");
          return;
      }
      break;
    }
    /* Event generated by reception of proprietary nxp act response. */
    case nci_evt_proprietary_nxp_act_rsp_rec: {

      nci_rf_mapping_config_t mapping_config_1 = {
          .rf_protocol  = nci_protocol_t2t,
          .mode         = nci_rf_mapping_mode_poll,
          .rf_interface = nci_rf_interface_frame
      };

      nci_rf_mapping_config_t mapping_config[1] = {mapping_config_1};

      nci_rf_discover_map_cmd_t cmd = {
          .num_of_mapping_config = 1,
          .mapping_config = mapping_config
      };

      nci_rf_discover_map(&cmd);
      break;
    }
    case nci_evt_rf_discover_map_rsp_rec: {

      if(nci_evt->data.payload.nci_data.rf_discover_map_rsp.status != nci_status_ok) {
          nci_log_ln("RF Discover Map Response status not ok.");
          return;
      }

      uint8_t config[] = {nci_nfc_a_passive_poll_mode, 1};

      nci_rf_discover_cmd_t cmd = {
          .num_of_config = 1,
          .configurations = config
      };

      nci_rf_discover(&cmd);
      break;
    }
    case nci_evt_rf_discover_rsp_rec: {
      if(nci_evt->data.payload.nci_data.rf_discover_rsp.status != nci_status_ok) {
          nci_log_ln("RF Discover Response status not ok.");
          return;
      }
      /* Wait for NTF */
      break;
    }
    case nci_evt_rf_intf_activated_ntf_rec: {

      uint8_t t2t_cmd_buff[] = {
          T2T_CMD_WRITE,
          write_index + 4,
          tlv_buff[write_index * 4],
          tlv_buff[write_index * 4 + 1],
          tlv_buff[write_index * 4 + 2],
          tlv_buff[write_index * 4 + 3]
      };

      nci_data_packet_t pakcet = {
          .pbf = nci_pbf_complete_msg,
          .conn_id = 0,
          .payload_len = 6,
          .payload = t2t_cmd_buff
      };
      nci_data_packet_send(&pakcet);
      break;
    }
    case nci_evt_data_packet_rec: {

      if (nci_evt->data.payload.nci_data.rec_data_packet.payload[0] != T2T_RSP_ACK) {
          printf("T2T Write NACK response. \r\n");
      }

      write_index++;

      int num_bytes_to_write = write_size - (write_index * 4);

      uint8_t t2t_cmd_buff[6] = {0};

      if (num_bytes_to_write > 0) {
          t2t_cmd_buff[0] = T2T_CMD_WRITE;
          t2t_cmd_buff[1] = write_index + 4;
          t2t_cmd_buff[2] = tlv_buff[write_index * 4];
          if (num_bytes_to_write >= 4) {
              t2t_cmd_buff[3] = tlv_buff[write_index * 4 + 1];
              t2t_cmd_buff[4] = tlv_buff[write_index * 4 + 2];
              t2t_cmd_buff[5] = tlv_buff[write_index * 4 + 3];
          }
          else if (num_bytes_to_write == 3) {
              t2t_cmd_buff[3] = tlv_buff[write_index * 4 + 1];
              t2t_cmd_buff[4] = tlv_buff[write_index * 4 + 2];
          }
          else if (num_bytes_to_write == 2) {
              t2t_cmd_buff[3] = tlv_buff[write_index * 4 + 1];
          }
          nci_data_packet_t pakcet = {
              .pbf = nci_pbf_complete_msg,
              .conn_id = 0,
              .payload_len = 6,
              .payload = t2t_cmd_buff
          };
          nci_data_packet_send(&pakcet);
      } else {
          printf("T2T write completed.\r\n");
          write_index = 0;
          nci_rf_deactivate_cmd_t cmd = {
              .deactivate_type = nci_rf_deact_type_discovery_mode
          };
          nci_rf_deactivate(&cmd);
      }

      break;
    }
    case nci_evt_core_conn_credits_ntf_rec: {
      break;
    }
    case nci_evt_rf_deactivate_rsp_rec: {
      break;
    }
    case nci_evt_rf_deactivate_ntf_rec: {
      break;
    }
    /* Meh */
    default:
      break;
  }
}

/**************************************************************************//**
 * @brief GPIO Odd IRQ for odd-numbered pins
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void) {
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << PN71x0_IRQ_PIN: {
      // Clear interrupt flag for PN71x0
      GPIO_IntClear(1 << PN71x0_IRQ_PIN);
      nci_notify_incoming_packet();
      break;
    }
  }
}

/**************************************************************************//**
 * @brief GPIO Even IRQ for even-numbered pins
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void) {
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << PN71x0_IRQ_PIN: {
      // Clear interrupt flag for PN71x0
      GPIO_IntClear(1 << PN71x0_IRQ_PIN);
      nci_notify_incoming_packet();
      break;
    }
  }
}
