#define _UART_DRV_C_
#include "uart_drv_int.h"

static uint8_t u8IsConfigured = 0;
static uint8_t tu8UartDrv_iRxBuffer[DeUartDrv_iBufferSize];
// static uint8_t tu8UartDrv_iTxBuffer[DeUartDrv_iBufferSize];

static TstUartDrv_iQueue stUartDrv_iRxQueue;
// static TstUartDrv_iQueue stUartDrv_iTxQueue;

static TeQueueRet eDataQueueInit(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Buffer, uint8_t Fu8Size);
static TeQueueRet eDataQueuePut(TstUartDrv_iQueue* FpstQueue, uint8_t Fu8Data);
static TeQueueRet eDataQueueGet(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Data);
static TeQueueRet eDataQueueDataAvailable(TstUartDrv_iQueue* FpstQueue);


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
		eDataQueueInit(&stUartDrv_iRxQueue, tu8UartDrv_iRxBuffer, DeUartDrv_iBufferSize);
		// u8DataQueueInit(&stUartDrv_iTxQueue, tu8UartDrv_iTxBuffer, DeUartDrv_iBufferSize);
		IEC0bits.U1TXIE = 0;
		IEC0bits.U1RXIE = 0;

		U1MODE = 0x0008;
		U1MODE |= FpstUartConfig->eStopBit;
		U1MODE |= (FpstUartConfig->eDataType << 1) & 0x06;
		U1STA = 0x00;
		U1BRG = (configCPU_CLOCK_HZ/(4u * FpstUartConfig->u32Baudrate)) - 1;
		
		U1MODEbits.UARTEN = 1;   // enabling UART ON bit
		U1STAbits.UTXEN = 1;
		eRetVal = CeUartDrv_eSuccess;
		u8IsConfigured = 1;
	}

	return(eRetVal);
}

TeUartDrv_eRetval eUartDrv_eTransmit(const uint8_t* Fpu8TxBuffer, uint16_t u16Fu16Size) {
	TeUartDrv_eRetval eRet = CeUartDrv_eSuccess;
	if (!u8IsConfigured) {
		eRet = CeUartDrv_eNotConfigured;
	}
	else if ((Fpu8TxBuffer == NULL) || (u16Fu16Size == 0)) {
		eRet = CeUartDrv_eBadParameter;
	}
	else {
		uint16_t u16Index = 0;
		uint8_t* pu8Data = (uint8_t*) Fpu8TxBuffer;
		while (u16Index < u16Fu16Size) {
			while (U1STAbits.UTXBF); // to be protected
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
	
	if (!u8IsConfigured) {
		eRet = CeUartDrv_eNotConfigured;
	}
	else if ((Fpu8TxBuffer == NULL) || (Fu16ReceiveSize == NULL)) {
		eRet = CeUartDrv_eBadParameter;
	}
	else if (*Fu16ReceiveSize == 0) {
		eRet = CeUartDrv_eBadParameter;
	}
	else {
		uint16_t u16Cnt = 0;
		TeQueueRet eQRet;
		do {
			eQRet = eDataQueueGet(&stUartDrv_iRxQueue, Fpu8TxBuffer);
			u16Cnt += (eQRet == CeQueue_Ok) ? 1 : 0;
		} while ((u16Cnt < *Fu16ReceiveSize) && (eQRet == CeQueue_Ok));

		*Fu16ReceiveSize = u16Cnt;
		if (!u16Cnt) {
			eRet = CeUartDrv_eNoDataAvailable;
		}
	}

	return(eRet);
}

TeUartDrv_eRetval eUartDrv_ePrint(char* FpcPrintText) {
	return( eUartDrv_eTransmit((const uint8_t*) FpcPrintText, strlen(FpcPrintText)) );
}

TeUartDrv_eRetval eUartDrv_eDataAvailable(void) {
	TeUartDrv_eRetval eRet = CeUartDrv_eSuccess;
	if(eDataQueueDataAvailable(&stUartDrv_iRxQueue) != CeQueue_Ok) {
		eRet = CeUartDrv_eError;
	}
	return(eRet);
}

/****************************************************************************
 * INTERNAL
 ****************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
	IFS0bits.U1RXIF = 0;
	uint8_t u8data = U1RXREG;
	eDataQueuePut(&stUartDrv_iRxQueue, u8data);
}

static TeQueueRet eDataQueueInit(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Buffer, uint8_t Fu8Size) {
	TeQueueRet eRet = CeQueue_Error;
	if ((FpstQueue != NULL) && (Fpu8Buffer != NULL) && (Fu8Size != 0)) {
		FpstQueue->pu8Head = Fpu8Buffer;
		FpstQueue->pu8Tail = Fpu8Buffer;
		FpstQueue->pu8Buffer = Fpu8Buffer;
		FpstQueue->u8Full = 0;
		FpstQueue->u8Size = Fu8Size;
		eRet = CeQueue_Ok;
	}

	return(eRet);
}

static TeQueueRet eDataQueuePut(TstUartDrv_iQueue* FpstQueue, uint8_t Fu8Data) {
	TeQueueRet eRet = CeQueue_Ok;
	if (FpstQueue->u8Full) {
		eRet = CeQueue_Full;
	}
	else {
		*(FpstQueue->pu8Tail) = Fu8Data;

		if ( (FpstQueue->pu8Tail != (FpstQueue->pu8Buffer + FpstQueue->u8Size - 1)) // no buffer wrap ?
		&& ((FpstQueue->pu8Tail + 1) != FpstQueue->pu8Head) ) { // no collision ?
			FpstQueue->pu8Tail++; // increment tail index
		}
		else if ( (FpstQueue->pu8Tail == (FpstQueue->pu8Buffer + FpstQueue->u8Size - 1)) // buffer wrap ?
		&& (FpstQueue->pu8Head != FpstQueue->pu8Buffer) ) { // no collision ?
			FpstQueue->pu8Tail = FpstQueue->pu8Buffer; // wrap, no collision
		}
		else {
			FpstQueue->u8Full = 1;
		}
	}

	return(eRet);
}

static TeQueueRet eDataQueueGet(TstUartDrv_iQueue* FpstQueue, uint8_t* Fpu8Data) {
	TeQueueRet eRet = CeQueue_Ok;
	if ((FpstQueue == NULL) && (Fpu8Data == NULL)) {
		eRet = CeQueue_Error;
	}
	else {
		if (FpstQueue->pu8Head != FpstQueue->pu8Tail) {
			*Fpu8Data = *FpstQueue->pu8Head;
			FpstQueue->pu8Head++;
			if (FpstQueue->pu8Head == (FpstQueue->pu8Buffer + FpstQueue->u8Size)) {
				FpstQueue->pu8Head = FpstQueue->pu8Buffer;
			}
		}
		else if ((FpstQueue->pu8Head == FpstQueue->pu8Tail) && FpstQueue->u8Full) {
			*Fpu8Data = *FpstQueue->pu8Head;
			FpstQueue->u8Full = 0;
		}
	}
	return(eRet);
}

static TeQueueRet eDataQueueDataAvailable(TstUartDrv_iQueue* FpstQueue) {
	TeQueueRet eRet = CeQueue_Ok;
	if ((FpstQueue->pu8Head == FpstQueue->pu8Tail) && !FpstQueue->u8Full) {
		eRet = CeQueue_Error;
	}
	return(eRet);
}