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
#include "serial.h"
#include "t2t.h"
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

//  uint8_t conn_credits = 0;
  uint16_t read_index = 0;
  uint16_t t2t_area_size = 0;

  uint8_t data_buff[16];

/*
 * T2T Read Process
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
 * DH --> NCI Data Message (READ Command, Block Address)                                                        <-- NFCC
 * DH <-- Core Conn Credits NTF                                                                                 <-- NFCC
 * DH <-- NCI Data Message (Read Response or NACK Response)                                                     <-- NFCC
 * ----- RF Deactivate Phase ------
 * DH --> RF Deactivate CMD (Discovery)                                                                         <-- NFCC
 * DH <-- RF Deactivate RSP                                                                                     <-- NFCC
 * DH --> RF Deactivate NTF                                                                                     <-- NFCC
 * ----- Go Back to RF Discover Phase ------
 */

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
  /* Initialize PN71x0 I2C communication. */
  pn71x0_init(init);
  /* Initialize NCI. */
  nci_init();
  /* Print project name. */
  printf("\r\n******************************\r\n*\r\n");
  printf("* NCI T2T Read Demo\r\n");
  printf("*\r\n******************************\r\n");

}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {

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
      nci_err_t nci_err = nci_core_reset(&core_reset_cmd);
      if (nci_err != nci_err_none) {
          printf("NCI core reset error: %x \r\n", nci_err);
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
      printf("NFCC's NCI Version is %x.%x \r\n", ((nci_version & 0xF0) >> 4), (nci_version & 0x0F));
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
      uint8_t t2t_cmd_buff[] = {T2T_CMD_READ, read_index};

      nci_data_packet_t pakcet = {
          .pbf = nci_pbf_complete_msg,
          .conn_id = 0,
          .payload_len = 2,
          .payload = t2t_cmd_buff
      };
      nci_data_packet_send(&pakcet);
      break;
    }
    case nci_evt_data_packet_rec: {

      memcpy(data_buff, nci_evt->data.payload.nci_data.rec_data_packet.payload, 16);

      if (read_index == 0) {
          /* CC2, convert to size in blocks. */
          t2t_area_size = data_buff[14] * 2;
          /* Print header area. */
          printf("\r\nHeader: \r\nBlock 000 ");
          serial_put_hex_and_ascii(&data_buff[0], 4);
          printf("\r\nBlock 001 ");
          serial_put_hex_and_ascii(&data_buff[4], 4);
          printf("\r\nBlock 002 ");
          serial_put_hex_and_ascii(&data_buff[8], 4);
          printf("\r\nBlock 003 ");
          serial_put_hex_and_ascii(&data_buff[12], 4);
          printf("\r\n\r\nT2T Area (Size: %d blocks): \r\n", t2t_area_size);
      }

      else if (((4 + t2t_area_size) - read_index) == 2) {
          printf("Block %03u to %03u ", read_index, (read_index + 1));
          serial_put_hex(data_buff, 8);
          printf(" -- -- -- -- -- -- -- --    ");
          serial_put_ascii(data_buff, 8);
          printf("\r\n");
      }

      else {
          printf("Block %03u to %03u ", read_index, (read_index + 3));
          serial_put_hex_and_ascii(data_buff, 16);
          printf("\r\n");
      }

      read_index += 4;

      if (read_index < (t2t_area_size + 4)) {

          uint8_t t2t_cmd_buff[] = {T2T_CMD_READ, read_index};

          nci_data_packet_t pakcet = {
              .pbf = nci_pbf_complete_msg,
              .conn_id = 0,
              .payload_len = 2,
              .payload = t2t_cmd_buff
          };
          nci_data_packet_send(&pakcet);
      }
      else {
          read_index = 0;
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
