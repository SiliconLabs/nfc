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
#include "em_gpio.h"
#include "nt3h2x11.h"
#include "sl_simple_led_instances.h"

/* Define your board here */
#define BRD4314A 1

/* EFR32xG12 Boards*/
#if    (BRD4103A == 1)\
    || (BRD4161A == 1)\
    || (BRD4162A == 1)\
    || (BRD4163A == 1)\
    || (BRD4164A == 1)

#define NT3H2X11_FD_PORT   gpioPortB
#define NT3H2X11_FD_PIN    (7)

#elif  (BRD4166A == 1)

#define NT3H2X11_FD_PORT   gpioPortF
#define NT3H2X11_FD_PIN    (4)

#elif  (BRD4170A == 1)

#define NT3H2X11_FD_PORT   gpioPortC
#define NT3H2X11_FD_PIN    (5)

#elif  (BRD4172A == 1)\
    || (BRD4172B == 1)\
    || (BRD4173A == 1)\
    || (BRD4304A == 1)

#define NT3H2X11_FD_PORT   gpioPortA
#define NT3H2X11_FD_PIN    (1)

/* EFR32xG13 Boards*/
#elif  (BRD4104A == 1)\
    || (BRD4158A == 1)\
    || (BRD4159A == 1)\
    || (BRD4167A == 1)\
    || (BRD4168A == 1)\
    || (BRD4174A == 1)\
    || (BRD4174B == 1)\
    || (BRD4175A == 1)\
    || (BRD4305A == 1)\
    || (BRD4305C == 1)\
    || (BRD4305D == 1)\
    || (BRD4305E == 1)\
    || (BRD4306A == 1)\
    || (BRD4306B == 1)\
    || (BRD4306C == 1)\
    || (BRD4306D == 1)\
    || (BRD4165B == 1)

#define NT3H2X11_FD_PORT   gpioPortA
#define NT3H2X11_FD_PIN    (1)

/* EFR32xG21 Boards*/
#elif  (BRD4180A == 1)\
    || (BRD4180B == 1)\
    || (BRD4181A == 1)\
    || (BRD4181B == 1)\
    || (BRD4181C == 1)\
    || (BRD4308A == 1)\
    || (BRD4308B == 1)

#define NT3H2X11_FD_PORT   gpioPortA
#define NT3H2X11_FD_PIN    (6)

#elif (BRD4309B == 1)

#error "No more pins for NT3H2x11 field detection for BRD4309B."

/* EFR32xG22 Boards*/
#elif  (BRD4182A == 1)\
    || (BRD4184A == 1)\
    || (BRD4310A == 1)\
    || (BRD4311A == 1)

#define NT3H2X11_FD_PORT   gpioPortA
#define NT3H2X11_FD_PIN    (6)

#elif  (BRD4183A == 1)

#error "No more pins for NT3H2x11 field detection for BRD4183A."

#elif  (BRD4314A == 1)

#define NT3H2X11_FD_PORT   gpioPortB
#define NT3H2X11_FD_PIN    (3)

#else
// custom board

#endif

#define NT3H2X11_FD_INIT_DEFAULT {                                  \
    true,                       /* Enable */                        \
    NT3H2X11_FD_PORT,           /* Field Detection GPIO Port */     \
    NT3H2X11_FD_PIN,            /* Field Detection GPIO Pin */      \
}

nt3h2x11_init_t nt3h2x11_init_only_fd = {
    .i2c_init = { .enable = false },
    .fd_init  = NT3H2X11_FD_INIT_DEFAULT
};

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  /* Enable FD pin interrupt. */
  nt3h2x11_init(nt3h2x11_init_only_fd);
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}

/***************************************************************************//**
 * GPIO Odd ISR.
 ******************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << NT3H2X11_FD_PIN: {
      // Clear interrupt flag
      GPIO_IntClear(1 << NT3H2X11_FD_PIN);
      // Toggle LED 0
      sl_led_toggle(&sl_led_led0);
      break;
    }
  }
}

/***************************************************************************//**
 * GPIO Even ISR.
 ******************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << NT3H2X11_FD_PIN: {
      // Clear interrupt flag
      GPIO_IntClear(1 << NT3H2X11_FD_PIN);
      // Toggle LED 0
      sl_led_toggle(&sl_led_led0);
      break;
    }
  }
}
