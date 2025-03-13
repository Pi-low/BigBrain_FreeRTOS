#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "FreeRTOS.h"

#define FLAG_CLI_MNG_ACTIVE	1
#define FLAG_CAN_MNG_ACTIVE 1

#if (configUSE_16_BIT_TICKS)
#define DeBsp_eWaitForever	(0xFFFF)
#endif

typedef enum
{
	CeWarning = 1,
	CeSuccess = 0,
	CeTimeout = -1,
	CeNotInitialized = -2,
	CeBadParameter = -3,
	CeNotConfigured = -4,
	CeDrvError = -5
} TeRetVal;

#endif //_CONFIG_H_