/****************************************************************************
 * @file main.c
 * @author Nello (nello.chom@protonmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 ****************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bsp.h"
#include "AppCli.h"

static void vApp_TaskMain(void *pvParameters);

int main(void)
{
	vBspStart();
	vAppCli_Init();
	eUartDrv_ePrint("Hello world !\r\n");
	if (xTaskCreate(vApp_TaskMain, "Main", configMINIMAL_STACK_SIZE * 3, NULL, tskIDLE_PRIORITY + 1, NULL) != pdTRUE)
	{
		eUartDrv_ePrint("Could not create \"Main\" task\r\n");
	}

    __builtin_enable_interrupts();
	vTaskStartScheduler();
	return (pdFALSE);
}

// void vApplicationIdleHook( void )
// {
// }

static void vApp_TaskMain(void *pvParameters)
{
	pvParameters = pvParameters;
	eUartDrv_ePrint("Main Task init\r\n");
	TickType_t xLastTick = xTaskGetTickCount();
	char tcDebug[100] = {0};

	for (;;)
	{
		snprintf(tcDebug, 100, "Scheduler tick: %u\r\n", xLastTick);
		eUartDrv_ePrint(tcDebug);
		xTaskDelayUntil(&xLastTick, 1000);
	}
}
