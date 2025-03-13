#ifndef _CLI_MNG_H_
#define _CLI_MNG_H_

#include "Config.h"
#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"

#if (FLAG_CLI_MNG_ACTIVE)
#define _CLI_MNG_ACTIVE
#endif

#ifdef _CLI_MNG_ACTIVE

extern void vCliMng_eEnableCli(void);
extern void vCliMng_eDisableCli(void);

#endif // _CLI_MNG_ACTIVE

#endif //_CLI_MNG_H_
