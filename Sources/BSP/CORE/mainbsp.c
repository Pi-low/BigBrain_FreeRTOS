#include <xc.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"

void vBspStart(void)
{
#ifdef _CLI_MNG_ACTIVE 
    if (xTaskCreate(vCliMng_eTask, DeCliMng_iTaskName, DeCliMng_iTaskStackSize, NULL, DeCliMng_iTaskPriority, NULL) != pdTRUE)
    {
        eUartDrv_ePrint("Could not create CliMng task");
    }
#endif
}

