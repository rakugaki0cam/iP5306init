/**
 * System Driver Source File
 * 
 * @file system.c
 * 
 * @ingroup systemdriver
 * 
 * @brief This file contains the API implementation for the System Driver.
 *
 * @version Driver Version 1.0.0
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

#include "../system.h"

/** 
* @ingroup systemdriver
* @brief Initializes the Peripheral Module Disable (PMD) module.
* @param None.
* @return None.
*/
void PMD_Initialize(void);

void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    EUSART_Initialize();
    I2C1_Initialize();
    PMD_Initialize();
    WDT_Initialize();
    INTERRUPT_Initialize();
}

void PMD_Initialize(void)
{
    //IOCMD IOC enabled; CLKRMD CLKR disabled; NVMMD NVM disabled; FVRMD FVR disabled; SYSCMD SYSCLK enabled; 
    PMD0 = 0x46;
    //TMR0MD TMR0 disabled; TMR1MD TMR1 disabled; TMR2MD TMR2 disabled; NCOMD DDS(NCO) disabled; TMR3MD TMR3 disabled; TMR4MD TMR4 disabled; TMR5MD TMR5 disabled; TMR6MD TMR6 disabled; 
    PMD1 = 0xFF;
    //CMP1MD CMP1 disabled; ADCMD ADC disabled; CMP2MD CMP2 disabled; DACMD DAC disabled; 
    PMD2 = 0x66;
    //CCP1MD CCP1 disabled; CCP2MD CCP2 disabled; PWM5MD PWM5 disabled; PWM6MD PWM6 disabled; CWG1MD CWG1 disabled; CCP3MD CCP3 disabled; CCP4MD CCP4 disabled; CWG2MD CWG2 disabled; 
    PMD3 = 0xFF;
    //MSSP1MD MSSP1 enabled; UART1MD EUSART enabled; MSSP2MD MSSP2 disabled; 
    PMD4 = 0x4;
    //CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; CLC3MD CLC3 disabled; CLC4MD CLC4 disabled; DSMMD DSM disabled; 
    PMD5 = 0x1F;
}

