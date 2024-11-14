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

#include "FreeRTOS.h"
#include "task.h"
#include "system.h"
#include "Pin_drv.h"
#include "uart_drv.h"
#include "Config.h"

static void vApp_MainTask(void *pvParameters);
TaskHandle_t xApp_Task01;

void main(void)
{
	CLOCK_Initialize();
	PIN_MANAGER_Initialize();
	if (xTaskCreate(vApp_MainTask, "Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xApp_Task01) != pdFALSE)  {
		if (xApp_Task01 != NULL) {
			xPortStartScheduler();
		}
	}

	for (;;)
	{
		
	}
}

// void vApplicationIdleHook( void )
// {
// }

static void vApp_MainTask(void *pvParameters) {
	pvParameters = pvParameters;
	TstUartDrv_eConfig stUartCfg = {115200, CeUartDrv_e8PN, CeUartDrv_eStop1Bit};
	eUartDrv_eInit(&stUartCfg);
	TickType_t xLastTick;
	char tcDebug[100] = {0};
	for (;;)
	{
		xLastTick = xTaskGetTickCount();
		snprintf(tcDebug, 100, "Scheduler tick: %u\r\n", xLastTick);
		eUartDrv_ePrint(tcDebug);
		xTaskDelayUntil(&xLastTick, 1000);
	}
}