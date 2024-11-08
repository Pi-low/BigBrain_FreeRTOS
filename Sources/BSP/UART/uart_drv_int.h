#ifndef _UART_DRV_INT_H_
#define _UART_DRV_INT_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "uart_drv_cfg.h"
#include "uart_drv.h"

#if DeUartDrv_iUartQModeEn
typedef struct {
	uint8_t * pu8Head;
	uint8_t * pu8Tail;
	uint8_t u8Full;
	uint8_t u8Size;
} TstUartDrv_iQueue;
#endif

#endif //_UART_DRV_INT_H