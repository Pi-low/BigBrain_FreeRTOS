#ifndef _CLI_MNG_INT_H_
#define _CLI_MNG_INT_H_

#include <stdio.h>
#include <string.h>

#include "cli_mng.h"

#ifdef _CLI_MNG_ACTIVE
#include "cli_mng_cfg.h"

extern void vCliMng_eTask(void *pvParameters);

#endif // _CLI_MNG_ACTIVE

#endif // _CLI_MNG_INT_H_