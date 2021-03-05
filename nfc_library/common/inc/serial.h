/***************************************************************************//**
 * @file   serial.h
 * @brief  APIs for custom serial output.
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

#ifndef __SERIAL_H__

/***************************************************************************//**
 * @addtogroup NFC Library
 * @brief Custom serial output APIs.
 * @{
 ******************************************************************************/

#define __SERIAL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void serial_put_hex (const uint8_t *data, const uint32_t length);

void serial_put_ascii (const uint8_t *data, const uint32_t length);

void serial_put_hex_and_ascii (const uint8_t *data, const uint32_t length);

#ifdef __cplusplus
}
#endif
/** @} (end addtogroup NFC Library) */
#endif

