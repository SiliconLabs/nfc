/***************************************************************************//**
 * @file   main.c
 * @brief  Example for NT3H2x11 field detection.
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

#include <stdio.h>
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "nt3h2x11.h"

/* Define your board here */
#define BRD4162A 1

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

/* Main function */
int main(void)
{
  // Device errata
  CHIP_Init();
  /* Initialize on-board LEDs. */
  BSP_LedsInit();
  /* Enable FD pin interrupt. */
  nt3h2x11_init(nt3h2x11_init_only_fd);
  /* Wait for FD pin interrupt. */
  while(1) {
    /* Use sleep function carefully as some boards may not be able to
     * talk to debugger again during sleep without recovery. */
    /* Demo NFC wake from sleep. */
//    EMU_EnterEM2(true);
  }

  return 0;
}

/* Put both GPIO ODD and EVEN ISR here for across-board compatibility. */

/* GPIO ODD IRQ for pushbuttons on odd-numbered pins */
void GPIO_ODD_IRQHandler(void)
{
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << NT3H2X11_FD_PIN: {
      // Clear interrupt flag
      GPIO_IntClear(1 << NT3H2X11_FD_PIN);
      // Toggle LED 0
      BSP_LedToggle(0);
      break;
    }
  }
}

/* GPIO EVEN IRQ for pushbuttons on even-numbered pins */
void GPIO_EVEN_IRQHandler(void)
{
  switch (GPIO_IntGet() & 0xFFFF){
    case 1 << NT3H2X11_FD_PIN: {
      // Clear interrupt flag
      GPIO_IntClear(1 << NT3H2X11_FD_PIN);
      // Toggle LED 0
      BSP_LedToggle(0);
      break;
    }
  }
}

