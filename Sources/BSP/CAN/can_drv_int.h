#ifndef _CAN_DRV_INT_H_
#define _CAN_DRV_INT_H_

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "can_drv.h"

#if (FLAG_CAN_MNG_ACTIVE)
#define _CAN_MNG_ACTIVE
#endif

#ifdef _CAN_MNG_ACTIVE
#include "can_drv_cfg.h"

#ifdef _CAN_DRV_C_
#endif //_CAN_DRV_C_


#endif // _CAN_MNG_ACTIVE

#endif // _CAN_DRV_INT_H_