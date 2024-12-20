#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "FreeRTOSConfig.h"

#define FLAG_CLI_MNG_ACTIVE	1

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