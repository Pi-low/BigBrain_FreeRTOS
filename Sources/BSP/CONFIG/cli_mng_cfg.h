#ifndef _CLI_MNG_CFG_H_
#define _CLI_MNG_CFG_H_

#ifdef _CLI_MNG_ACTIVE
#include "FreeRTOS.h"
#include "task.h"

#ifdef _CLI_MNG_C_
#define DeCliMng_iCmdBufSize	128
#define DeCliMng_iOutBufSize	512
#define DeCliMng_iSubBufSize	64

#define DeCliMng_iCR			'\r'
#define DeCliMng_iLF			'\n'
#define DeCliMng_iCRLF			"\r\n"
#endif // _CLI_MNG_C_

#define DeCliMng_iTaskPeriod	100 // in ms
#define DeCliMng_iTaskPriority	(tskIDLE_PRIORITY + 1)
#define DeCliMng_iTaskStackSize	(configMINIMAL_STACK_SIZE * 4)
#define DeCliMng_iTaskName		"CliMng"


#endif

#endif // _CLI_MNG_CFG_H_