/****************************************************************************
 * @file main.c
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
#include "system.h"
#include "uart_drv.h"

void main(void)
{
    CLOCK_Initialize();
    for (;;)
    {
        
    }
}

void vApplicationIdleHook( void )
{
    
}