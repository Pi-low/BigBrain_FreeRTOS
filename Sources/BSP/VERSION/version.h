/** 
 * @file    Version.h
 * @author  Nello
 * @date    February 13, 2023, 11:18 PM
 * 
 */

#ifndef VERSION_H
#define	VERSION_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>

/******************************************************************************
 * Definitions and macros
 *****************************************************************************/

/******************************************************************************
 * Type definitions
 *****************************************************************************/
#define SW_VERSION (0x0100)

/******************************************************************************
 * Extern/global variables
 *****************************************************************************/

/******************************************************************************
 * Public function prototypes
 *****************************************************************************/
extern const char SWDescription[];
extern const uint16_t SWVersion;

#endif	/* VERSION_H */