#include <xc.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "uart_drv_int.h"
#include "cli_mng_int.h"

void vBspStart(void)
{
    PIN_MANAGER_Initialize();
	CLOCK_Initialize();
    TstUartDrv_eConfig stUartCfg = {115200, CeUartDrv_e8PN, CeUartDrv_eStop1Bit};
	eUartDrv_eInit(&stUartCfg);
#ifdef _CLI_MNG_ACTIVE 
    if (xTaskCreate(vCliMng_eTask, DeCliMng_iTaskName, DeCliMng_iTaskStackSize, NULL, DeCliMng_iTaskPriority, NULL) != pdTRUE)
    {
        eUartDrv_ePrint("Could not create CliMng task");
    }
#endif
}

