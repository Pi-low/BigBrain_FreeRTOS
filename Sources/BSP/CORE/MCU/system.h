/****************************************************************************
 * @file system.h
 * @author Nello (nello.chom@protonmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
****************************************************************************/
#include <xc.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

extern void CLOCK_Initialize(void);