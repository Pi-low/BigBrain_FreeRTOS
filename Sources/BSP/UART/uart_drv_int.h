#ifndef _UART_DRV_INT_H_
#define _UART_DRV_INT_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "uart_drv.h"

#ifdef  _UART_DRV_C_
#include "uart_drv_cfg.h"
typedef enum
{
	CeQueue_Ok = 0,
	CeQueue_Error = -1,
	CeQueue_Full = -2
} TeQueueRet;

typedef struct
{
	uint8_t *pu8Head;
	uint8_t *pu8Tail;
	uint8_t *pu8Buffer;
	uint8_t u8Full;
	uint8_t u8Size;
} TstUartDrv_iQueue;

typedef struct
{
	uint8_t u8ConfigFlag;
	SemaphoreHandle_t xSemaRx;
	SemaphoreHandle_t xSemaTx;
} TstUartDrv_iHandle;

#endif //_UART_DRV_C_

#endif //_UART_DRV_INT_H