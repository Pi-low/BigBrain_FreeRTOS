/****************************************************************************
 * @file Pin_drv.c
 * @author Nello (nello.chom@protonmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 ****************************************************************************/

#include <xc.h>

void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0600;
    LATB = 0x1500;
    LATC = 0x00C8;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x0187;
    TRISB = 0xFCEF;
    TRISC = 0x03B5;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0002;
    ANSELB = 0x0003;
    ANSELC = 0x0034;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPINR26bits.C2RXR = 0x0018;    //RA8->ECAN2:C2RX
    RPOR1bits.RP36R = 0x000F;    //RB4->ECAN2:C2TX
    RPOR0bits.RP20R = 0x0031;    //RA4->INTERNAL OSCILLATOR:REFCLK
    RPINR18bits.U1RXR = 0x0027;    //RB7->UART1:U1RX
    RPOR5bits.RP49R = 0x000E;    //RC1->ECAN1:C1TX
    RPOR3bits.RP41R = 0x0003;    //RB9->UART2:U2TX
    RPOR3bits.RP40R = 0x0001;    //RB8->UART1:U1TX
    RPINR26bits.C1RXR = 0x0030;    //RC0->ECAN1:C1RX
    RPINR19bits.U2RXR = 0x0037;    //RC7->UART2:U2RX

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
}