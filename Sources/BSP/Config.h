#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "FreeRTOSConfig.h"

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