#ifndef _UART_DRV_H_
#define _UART_DRV_H_

#include <xc.h>
#include "Config.h"

typedef enum {
	CeUartDrv_eNoDataAvailable	= CeWarning + 1,
	CeUartDrv_eWarning			= CeWarning,
	CeUartDrv_eSuccess			= CeSuccess,
	CeUartDrv_eNotInitialized	= CeNotInitialized,
	CeUartDrv_eBadParameter		= CeBadParameter,
	CeUartDrv_eNotConfigured	= CeNotConfigured,
	CeUartDrv_eError			= CeDrvError,
} TeUartDrv_eRetval;

typedef enum {
	CeUartDrv_e8PN = 0,
	CeUartDrv_e8PE = 1,
	CeUartDrv_e8PO = 2,
	CeUartDrv_e9PN = 3
} TeUartDrv_eDataType;

typedef enum {
	CeUartDrv_eStop1Bit = 0,
	CeUartDrv_eStop2Bit
} TeUartDrv_eStopBit;

typedef struct {
	uint32_t u32Baudrate;
	TeUartDrv_eDataType eDataType;
	TeUartDrv_eStopBit eStopBit;
} TstUartDrv_eConfig;

// typedef void TfUartDrv_eCallback(void* FvArg);

extern TeUartDrv_eRetval eUartDrv_eInit(TstUartDrv_eConfig* FpstUartConfig);
extern TeUartDrv_eRetval eUartDrv_eTransmit(const uint8_t *Fpu8TxBuffer, uint16_t u16Fu16Size);
extern TeUartDrv_eRetval eUartDrv_eReceive(uint8_t* Fpu8TxBuffer, uint16_t* Fu16ReceiveSize);
extern TeUartDrv_eRetval eUartDrv_eDataAvailable(void);

#endif //_UART_DRV_H_