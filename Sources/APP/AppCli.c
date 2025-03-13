#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bsp.h"

static BaseType_t pFnCli_Set(char* FpcWriteBuff, size_t FxBuffSize, const char* FCpcParam);

static CLI_Command_Definition_t xCmd_Set = {
    "set",
    "set specific data",
    pFnCli_Set,
    -1
};

void vAppCli_Init(void)
{
    FreeRTOS_CLIRegisterCommand(&xCmd_Set);
    vCliMng_eEnableCli();
}

static BaseType_t pFnCli_Set(char* FpcWriteBuff, size_t FxBuffSize, const char* FCpcParam)
{
    BaseType_t xSzPar1, xSzPar2;
    memset(FpcWriteBuff, 0, FxBuffSize);
    const char* CpcPar1 = FreeRTOS_CLIGetParameter(FCpcParam, 1, &xSzPar1);
    const char* CpcPar2 = FreeRTOS_CLIGetParameter(FCpcParam, 2, &xSzPar2);
    if (CpcPar1 && CpcPar2)
    {
        snprintf(FpcWriteBuff, FxBuffSize, "Set %s : %s -> OK\r\n", CpcPar1, CpcPar2);
    }
    return 0;
}