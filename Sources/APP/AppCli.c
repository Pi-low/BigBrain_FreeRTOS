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

/****************************************************************************
 * @brief Testing CLI function
 * 
 * @param FpcWriteBuff 
 * @param FxBuffSize 
 * @param FCpcParam 
 * @return BaseType_t 
****************************************************************************/
static BaseType_t pFnCli_Set(char* FpcWriteBuff, size_t FxBuffSize, const char* FCpcParam)
{
    BaseType_t xSzPar1, xSzPar2;
    memset(FpcWriteBuff, 0, FxBuffSize);
    const char* CpcPar1 = FreeRTOS_CLIGetParameter(FCpcParam, 1, &xSzPar1);
    const char* CpcPar2 = FreeRTOS_CLIGetParameter(FCpcParam, 2, &xSzPar2);
    if (CpcPar1 && CpcPar2)
    {
        char * pcTrim1 = pvPortMalloc(xSzPar1 + 1);
        char * pcTrim2 = pvPortMalloc(xSzPar2 + 1);

        if (!pcTrim1 || !pcTrim2)
        {
            snprintf(FpcWriteBuff, FxBuffSize, "Set : Malloc error !\r\n");
            return 0;
        }
        else
        {
            memset(pcTrim1, 0, xSzPar1 + 1);
            memset(pcTrim2, 0, xSzPar2 + 1);
            memcpy(pcTrim1, CpcPar1, xSzPar1);
            memcpy(pcTrim2, CpcPar2, xSzPar2);
            snprintf(FpcWriteBuff, FxBuffSize, "Set \"%s\" : \"%s\" -> OK\r\n", pcTrim1, pcTrim2);
            vPortFree(pcTrim1);
            vPortFree(pcTrim2);
        }
    }
    return 0;
}