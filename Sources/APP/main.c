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

void main(void)
{
	PIN_MANAGER_Initialize();
	CLOCK_Initialize();
	// __builtin_enable_interrupts();
	xTaskCreate(vApp_MainTask, "Main", configMINIMAL_STACK_SIZE*4, NULL, tskIDLE_PRIORITY+1, NULL);
	vTaskStartScheduler();
}

// void vApplicationIdleHook( void )
// {
// }

static void vApp_MainTask(void *pvParameters) {
	pvParameters = pvParameters;
	TstUartDrv_eConfig stUartCfg = {115200, CeUartDrv_e8PN, CeUartDrv_eStop1Bit};
	eUartDrv_eInit(&stUartCfg);
	TickType_t xLastTick = xTaskGetTickCount();
	char tcDebug[100] = {0};
	char tcRxData[100] = {0};
	uint16_t u16BuffLen = 0;
	
	for (;;)
	{
		xTaskDelayUntil(&xLastTick, 1000);
		u16BuffLen = 100;
		snprintf(tcDebug, 100, "Scheduler tick: %u\r\n", xLastTick);
		eUartDrv_ePrint(tcDebug);
		if (eUartDrv_eReceive((uint8_t*)tcRxData, &u16BuffLen) == CeUartDrv_eSuccess) {
			tcRxData[u16BuffLen] = 0;
			snprintf(tcDebug, 100, "[RX] (%u) : %s\r\n", u16BuffLen, tcRxData);
			eUartDrv_ePrint(tcDebug);
		}
	}
}