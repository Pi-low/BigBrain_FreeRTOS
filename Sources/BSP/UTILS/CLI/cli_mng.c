#define _CLI_MNG_C_

#include "cli_mng_int.h"

#ifdef _CLI_MNG_ACTIVE

static uint8_t u8CliMng_iEnableFlag = 0;

void vCliMng_eTask(void *pvParameters)
{
	pvParameters = pvParameters;
	uint8_t tu8CliMng_iCmdBuff[DeCliMng_iCmdBufSize] = {0};
	uint8_t tu8CliMng_iOutBuff[DeCliMng_iOutBufSize] = {0};
	TickType_t xLastTick = xTaskGetTickCount();
	uint16_t u16RxCnt = DeCliMng_iSubBufSize;
	uint16_t u16DataCnt = 0;
	uint8_t *pu8Wd = tu8CliMng_iCmdBuff, *pu8Cr = NULL;
	for (;;)
	{
		if (eUartDrv_eReceive(pu8Wd, &u16RxCnt, DeBsp_eWaitForever) == CeUartDrv_eSuccess)
		{
			u16DataCnt += u16RxCnt;
			pu8Cr = (uint8_t*) strchr((const char*)pu8Wd, DeCliMng_iCR);
			if ((pu8Cr != NULL) || (u16DataCnt >= DeCliMng_iCmdBufSize)) //end of line, buffer full, process the receive command
			{
				*pu8Cr = 0; // trim <cr> char
				if (u8CliMng_iEnableFlag)
				{
					BaseType_t xMoreDataToFollow;
					do
					{
						xMoreDataToFollow = FreeRTOS_CLIProcessCommand((const char*)tu8CliMng_iCmdBuff, (char*) tu8CliMng_iOutBuff, DeCliMng_iOutBufSize);
						eUartDrv_ePrint((char*)tu8CliMng_iOutBuff);
					}
					while (xMoreDataToFollow != pdFALSE);
				}
				memset(tu8CliMng_iCmdBuff, 0, DeCliMng_iCmdBufSize);
			}
			else if (u16DataCnt < DeCliMng_iCmdBufSize)
			{
				pu8Wd += u16RxCnt;
				u16RxCnt = (DeCliMng_iCmdBufSize - u16DataCnt);
			}
		}
		else if (u16DataCnt >= DeCliMng_iCmdBufSize)
		{
			// end of line not detected, buffer full, flush buffer
			memset(tu8CliMng_iCmdBuff, 0, DeCliMng_iCmdBufSize);
			u16DataCnt = 0;
			u16RxCnt = DeCliMng_iSubBufSize;
			pu8Wd = tu8CliMng_iCmdBuff;
		}
		__builtin_clrwdt();
		xTaskDelayUntil(&xLastTick, pdMS_TO_TICKS(DeCliMng_iTaskPeriod));
	}
}

void vCliMng_eEnableCli(void)
{
	u8CliMng_iEnableFlag = 1;
}

void vCliMng_eDisableCli(void)
{
	u8CliMng_iEnableFlag = 0;
}

#endif // _CLI_MNG_ACTIVE
