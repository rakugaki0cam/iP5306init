/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

void (*IP5306_IRQ_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATC = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x2F;
    TRISC = 0x27;

    /**
    ANSELx registers
    */
    ANSELA = 0x23;
    ANSELC = 0x4;

    /**
    WPUx registers
    */
    WPUA = 0x4;
    WPUC = 0x0;
  
    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    ODCONC = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0x33;
    SLRCONC = 0x7;
    /**
    INLVLx registers
    */
    INLVLA = 0x2B;
    INLVLC = 0x7;

    /**
    PPS registers
    */
    INTPPS = 0x2; //RA2->INTERRUPT MANAGER:INT;
    RA4PPS = 20;  //RA4->EUSART:TX;
    SSP1CLKPPS = 0x10;  //RC0->MSSP1:SCL1;
    RC0PPS = 24;  //RC0->MSSP1:SCL1;
    SSP1DATPPS = 0x11;  //RC1->MSSP1:SDA1;
    RC1PPS = 25;  //RC1->MSSP1:SDA1;

    /**
    APFCON registers
    */

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCCP = 0x20;
    IOCCN = 0x0;
    IOCCF = 0x0;

    IP5306_IRQ_SetInterruptHandler(IP5306_IRQ_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IP5306_IRQ}
    if(IOCCFbits.IOCCF5 == 1)
    {
        IP5306_IRQ_ISR();  
    }
}
   
/**
   IP5306_IRQ Interrupt Service Routine
*/
void IP5306_IRQ_ISR(void) {

    // Add custom IOCCF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IP5306_IRQ_InterruptHandler)
    {
        IP5306_IRQ_InterruptHandler();
    }
    IOCCFbits.IOCCF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF5 at application runtime
*/
void IP5306_IRQ_SetInterruptHandler(void (* InterruptHandler)(void)){
    IP5306_IRQ_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF5
*/
void IP5306_IRQ_DefaultInterruptHandler(void){
    // add your IP5306_IRQ interrupt custom code
    // or set custom function using IP5306_IRQ_SetInterruptHandler()
}
/**
 End of File
*/