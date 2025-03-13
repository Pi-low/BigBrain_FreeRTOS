#ifndef _CAN_DRV_H_
#define _CAN_DRV_H_

#include "Config.h"

typedef enum
{
	CeCanDrv_eCAN1,
	CeCanDrv_eCAN2,
} TeCanDrv_eCanModule;

typedef enum
{
	CeCanDrv_e100KBaud = 0,
	CeCanDrv_e125KBaud,
	CeCanDrv_e200KBaud,
	CeCanDrv_e250KBaud,
	CeCanDrv_e500KBaud,
} TeCanDrv_eBaudrate;

typedef enum
{
	CeCanDrv_eModeNormalOp		= 0,
	CeCanDrv_eModeDisable		= 1,
	CeCanDrv_eModeLoopback		= 2,
	CeCanDrv_eModeListen		= 3,
	CeCanDrv_eModeConfigure		= 4,
	CeCanDrv_eModeListenAll		= 7
} TeCanDrv_eOperationMode;

typedef enum
{
	CeCanDrv_eFrameStd = 0,
	CeCanDrv_eFrameExt = 1,
} TeCanDrv_eIdType;

typedef enum
{
	CeCanDrv_eFrameData		= 0,
	CeCanDrv_eFrameRtr		= 1,
} TeCanDrv_eFrameType;

typedef enum
{
	CeCanDrv_ePriorityHigh		= 0b11,
	CeCanDrv_ePriorityMedium	= 0b10,
	CeCanDrv_ePriorityLow		= 0b01,
	CeCanDrv_ePriorityNone		= 0b00
} TeCanDrv_eTxPriority;

typedef union 
{
	uint8_t u8Raw;
	struct {
		uint8_t u8IdTyp			: 1; //< 1 bit (Standard Frame or Extended Frame)
		uint8_t u8FrmTyp		: 1; //< 1 bit (Data Frame or RTR Frame)
		uint8_t u8Dlc			: 4; //< 4 bit (No of data bytes a message frame contains)
		uint8_t u8Resv			: 2; //< 2 bit (Reserved bit)
	}bit;
} TnCanDrv_eField;

typedef struct
{
	uint32_t u32Identifier;		//< 29 bit (SID: 11bit, EID:18bit)
	TnCanDrv_eField nField;
	uint8_t *pu8Payload;		//< Frame data
} TstCanDrv_eFrame;

#endif // _CAN_DRV_H_