/**
 * @file    Version.c
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:34 PM
 * 
 */

#include <stdint.h>
#include "version.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/
#ifdef _DEBUG
const char __attribute__((address(0x280), space(prog))) SWDescription[128] = __DATE__" "__TIME__" : BigBrain tester application";
#else
const char __attribute__((address(0x280), space(prog))) SWDescription[128] = __DATE__" "__TIME__" : BigBrain CAN GW application";
#endif
const uint16_t SWVersion __attribute__((address(0x300), space(prog))) = SW_VERSION;