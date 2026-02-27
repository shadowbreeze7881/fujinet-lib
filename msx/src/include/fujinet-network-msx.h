/**
 * @brief   FujiNet Network Device Header
 * @author  Andy Narain
 * @email   theretrolife at soulexi dot com
 * @license gpl v. 3, see LICENSE for details.
 * @verbose Private
 */

#ifndef FUJINET_NETWORK_MSX_H
#define FUJINET_NETWORK_MSX_H

#include <stdint.h>
#include <msx.h>

uint8_t getDeviceNumber(const char* input, const char** afterDeviceSpec);
