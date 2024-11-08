#define _UART_DRV_C_
#include "uart_drv_int.h"


static uint8_t tu8UartDrv_iRxBuffer[DeUartDrv_iBufferSize];
// static uint8_t tu8UartDrv_iTxBuffer[DeUartDrv_iBufferSize];

#if DeUartDrv_iUartQModeEn

static TstUartDrv_iQueue stUartDrv_iRxQueue;
// static TstUartDrv_iQueue stUartDrv_iTxQueue;

static uint8_t u8DataQueueInit(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Buffer, uint8_t Fu8Size);
static uint8_t u8DataQueuePut(TstUartDrv_iQueue* FpstQueue, uint8_t Fu8Data);
static uint8_t u8DataQueueGet(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Data);
static uint8_t u8DataQueueSta(TstUartDrv_iQueue* FpstQueue);

#endif

// static tfUartDrv_eCallback *pfUartDrv_iU1Notify;
// static tfUartDrv_eCallback *pfUartDrv_iU2Notify;

TeUartDrv_eRetval eUartDrv_eInit(TstUartDrv_eConfig* FpstUartConfig) {
	TeUartDrv_eRetval eRetVal = CeUartDrv_eError;

	if (FpstUartConfig == NULL) {
		eRetVal = CeUartDrv_eBadParameter;
	}
	else if ((FpstUartConfig->u32Baudrate <= DeUartDrv_iBaudLowLimit)
	|| (FpstUartConfig->u32Baudrate > DeUartDrv_iBaudHighLimit)
	|| (FpstUartConfig->eDataType > CeUartDrv_e9PN)
	|| (FpstUartConfig->eStopBit > CeUartDrv_eStop2Bit)) {
		eRetVal = CeUartDrv_eBadParameter;
	}
	else {
#if DeUartDrv_iUartQModeEn
		u8DataQueueInit(&stUartDrv_iRxQueue, tu8UartDrv_iRxBuffer, DeUartDrv_iBufferSize);
		// u8DataQueueInit(&stUartDrv_iTxQueue, tu8UartDrv_iTxBuffer, DeUartDrv_iBufferSize);
#endif
		IEC0bits.U1TXIE = 0;
		IEC0bits.U1RXIE = 0;

		U1MODE = 0x0008;
		U1MODE |= FpstUartConfig->eStopBit;
		U1MODE |= (FpstUartConfig->eDataType << 1) & 0x06;
		U1STA = 0x00;
		U1BRG = (_FOSC_2_/(4u * FpstUartConfig->u32Baudrate)) - 1;
		
		U1MODEbits.UARTEN = 1;   // enabling UART ON bit
		U1STAbits.UTXEN = 1;
		eRetVal = CeUartDrv_eSuccess;
	}

	return(eRetVal);
}

TeUartDrv_eRetval eUartDrv_eTransmit(const uint8_t* Fpu8TxBuffer, uint16_t u16Fu16Size) {
	TeUartDrv_eRetval eRet = CeUartDrv_eSuccess;
	if (Fpu8TxBuffer == NULL || u16Fu16Size == 0) {
		eRet = CeUartDrv_eBadParameter;
	}
	else {
		uint16_t u16Index = 0;
		uint8_t* pu8Data = (uint8_t*) Fpu8TxBuffer;
		while (u16Index < u16Fu16Size) {
			while (U1STAbits.UTXBF); // to protect
			U1TXREG = *pu8Data;
			u16Index++;
			pu8Data++;
		}
		if (U1STAbits.UTXBF) {
			eRet = CeUartDrv_eWarning;
		}
	}

	return(eRet);
}

TeUartDrv_eRetval eUartDrv_eReceive(uint8_t* Fpu8TxBuffer, uint16_t* Fu16ReceiveSize) {
	TeUartDrv_eRetval eRet = CeUartDrv_eSuccess;
	
	if ((Fpu8TxBuffer == NULL) || (Fu16ReceiveSize == NULL)) {
		eRet = CeUartDrv_eBadParameter;
	}
	else if (*Fu16ReceiveSize == 0) {
		eRet = CeUartDrv_eBadParameter;
	}
	else {
		uint16_t u16Cnt = 0;
		uint8_t u8Qret = 0;
		do {
#if DeUartDrv_iUartQModeEn
			u8Qret = u8DataQueueGet(&stUartDrv_iRxQueue, Fpu8TxBuffer);
#endif
			u16Cnt += u8Qret;
		} while ((u16Cnt < *Fu16ReceiveSize) && u8Qret);

		*Fu16ReceiveSize = u16Cnt;
		if (!u16Cnt) {
			eRet = CeUartDrv_eNoDataAvailable;
		}
	}

	return(eRet);
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	IFS0bits.U1RXIF = 0;
	uint8_t u8data = U1RXREG;
#if DeUartDrv_iUartQModeEn
	u8DataQueuePut(&stUartDrv_iRxQueue, u8data);
#endif
}

#if DeUartDrv_iUartQModeEn

TeUartDrv_eRetval eUartDrv_eDataAvailable(void) {
	TeUartDrv_eRetval eRet = CeUartDrv_eSuccess;
	if(!u8DataQueueSta(&stUartDrv_iRxQueue)) {
		eRet = CeUartDrv_eError;
	}
	return(eRet);
}

static uint8_t u8DataQueueInit(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Buffer, uint8_t Fu8Size) {
	uint8_t u8Ret = 0;
	if ((FpstQueue != NULL) && (Fpu8Buffer != NULL) && (Fu8Size != 0)) {
		FpstQueue->pu8Head = Fpu8Buffer;
		FpstQueue->pu8Tail = Fpu8Buffer;
		FpstQueue->u8Full = 0;
		FpstQueue->u8Size = Fu8Size;
		u8Ret = 1;
	}

	return(u8Ret);
}

static uint8_t u8DataQueuePut(TstUartDrv_iQueue* FpstQueue, uint8_t Fu8Data) {
	*(FpstQueue->pu8Tail) = Fu8Data;

	if ((FpstQueue->pu8Tail != (FpstQueue->pu8Head + FpstQueue->u8Size - 1))
	&& (FpstQueue->pu8Tail + 1) != FpstQueue->pu8Head) {
		FpstQueue->pu8Tail++;
	}
	else if ((FpstQueue->pu8Tail == (FpstQueue->pu8Head + FpstQueue->u8Size - 1))
	&& (FpstQueue->pu8Head !=  FpstQueue->pu8Tail)) {
		FpstQueue->pu8Tail = FpstQueue->pu8Head;
	}
	else { // queue full
		FpstQueue->u8Full = 1;
	}

	return(FpstQueue->u8Full);
}

static uint8_t u8DataQueueGet(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Data) {
	uint8_t u8Ret = 0;
	if ((FpstQueue != NULL) && (Fpu8Data != NULL)) {
		if (((FpstQueue->pu8Head == FpstQueue->pu8Tail) && FpstQueue->u8Full)
		|| (FpstQueue->pu8Head != FpstQueue->pu8Tail)) {
			u8Ret = 1;
			*Fpu8Data = *FpstQueue->pu8Head;
			FpstQueue->pu8Head++;
			if (FpstQueue->u8Full) {
				FpstQueue->u8Full = 0;
			}
		}
	}
	
	return(u8Ret);
}

static uint8_t u8DataQueueSta(TstUartDrv_iQueue* FpstQueue) {
	return(((FpstQueue->pu8Head != FpstQueue->pu8Tail) || FpstQueue->u8Full) ? 1 : 0);
}
#endif //DeUartDrv_iUartQModeEn