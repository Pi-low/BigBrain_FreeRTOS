#ifndef _UART_DRV_INT_H_
#define _UART_DRV_INT_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "uart_drv_cfg.h"
#include "uart_drv.h"

typedef enum{
	CeQueue_Ok = 0,
	CeQueue_Error = -1,
	CeQueue_Full = -2
} TeQueueRet;

typedef struct {
	uint8_t * pu8Head;
	uint8_t * pu8Tail;
	uint8_t * pu8Buffer;
	uint8_t u8Full;
	uint8_t u8Size;
} TstUartDrv_iQueue;

#endif //_UART_DRV_INT_H