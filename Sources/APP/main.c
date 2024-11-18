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

static void vApp_TaskMain(void *pvParameters);
static void vApp_TaskSerial(void *pvParameters);

void main(void)
{
	PIN_MANAGER_Initialize();
	CLOCK_Initialize();
	TstUartDrv_eConfig stUartCfg = {115200, CeUartDrv_e8PN, CeUartDrv_eStop1Bit};
	eUartDrv_eInit(&stUartCfg);
	xTaskCreate(vApp_TaskMain, "Main", configMINIMAL_STACK_SIZE * 3, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(vApp_TaskSerial, "Serial", configMINIMAL_STACK_SIZE * 3, NULL, tskIDLE_PRIORITY + 1, NULL);
	__builtin_enable_interrupts();
	vTaskStartScheduler();
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

static void vApp_TaskSerial(void *pvParameters)
{
	pvParameters = pvParameters;
	eUartDrv_ePrint("Serial Task init\r\n");
	uint16_t u16BuffLen = 0;
	char tcRxData[100] = {0};
	char tcDebug[200] = {0};
	TickType_t xLastTick = xTaskGetTickCount();
	for (;;)
	{
		u16BuffLen = 100;
		if (eUartDrv_eReceive((uint8_t *)tcRxData, &u16BuffLen, 50) == CeUartDrv_eSuccess)
		{
			tcRxData[u16BuffLen] = 0;
			snprintf(tcDebug, 200, "[RX] (%u) : %s\r\n", u16BuffLen, tcRxData);
			eUartDrv_ePrint(tcDebug);
		}
		xTaskDelayUntil(&xLastTick, 100);
	}
}