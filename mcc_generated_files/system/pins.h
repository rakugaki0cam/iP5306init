/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA2 aliases
#define MAIN_SW_TRIS                 TRISAbits.TRISA2
#define MAIN_SW_LAT                  LATAbits.LATA2
#define MAIN_SW_PORT                 PORTAbits.RA2
#define MAIN_SW_WPU                  WPUAbits.WPUA2
#define MAIN_SW_OD                   ODCONAbits.ODCA2
#define MAIN_SW_ANS                  ANSELAbits.ANSA2
#define MAIN_SW_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define MAIN_SW_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define MAIN_SW_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define MAIN_SW_GetValue()           PORTAbits.RA2
#define MAIN_SW_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define MAIN_SW_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define MAIN_SW_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define MAIN_SW_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define MAIN_SW_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define MAIN_SW_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define MAIN_SW_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define MAIN_SW_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define IO_RA4_TRIS                 TRISAbits.TRISA4
#define IO_RA4_LAT                  LATAbits.LATA4
#define IO_RA4_PORT                 PORTAbits.RA4
#define IO_RA4_WPU                  WPUAbits.WPUA4
#define IO_RA4_OD                   ODCONAbits.ODCA4
#define IO_RA4_ANS                  ANSELAbits.ANSA4
#define IO_RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_RA4_GetValue()           PORTAbits.RA4
#define IO_RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_RA4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_RA4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_RA4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_RA4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_RA4_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define IO_RA4_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RC0 aliases
#define IO_RC0_TRIS                 TRISCbits.TRISC0
#define IO_RC0_LAT                  LATCbits.LATC0
#define IO_RC0_PORT                 PORTCbits.RC0
#define IO_RC0_WPU                  WPUCbits.WPUC0
#define IO_RC0_OD                   ODCONCbits.ODCC0
#define IO_RC0_ANS                  ANSELCbits.ANSC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_RC0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_RC0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_RC0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_RC0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_RC0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define IO_RC0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define IO_RC1_TRIS                 TRISCbits.TRISC1
#define IO_RC1_LAT                  LATCbits.LATC1
#define IO_RC1_PORT                 PORTCbits.RC1
#define IO_RC1_WPU                  WPUCbits.WPUC1
#define IO_RC1_OD                   ODCONCbits.ODCC1
#define IO_RC1_ANS                  ANSELCbits.ANSC1
#define IO_RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_RC1_GetValue()           PORTCbits.RC1
#define IO_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_RC1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define IO_RC1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define IO_RC1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define IO_RC1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define IO_RC1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define IO_RC1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC3 aliases
#define BOOST5V_SW_TRIS                 TRISCbits.TRISC3
#define BOOST5V_SW_LAT                  LATCbits.LATC3
#define BOOST5V_SW_PORT                 PORTCbits.RC3
#define BOOST5V_SW_WPU                  WPUCbits.WPUC3
#define BOOST5V_SW_OD                   ODCONCbits.ODCC3
#define BOOST5V_SW_ANS                  ANSELCbits.ANSC3
#define BOOST5V_SW_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define BOOST5V_SW_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define BOOST5V_SW_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define BOOST5V_SW_GetValue()           PORTCbits.RC3
#define BOOST5V_SW_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define BOOST5V_SW_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define BOOST5V_SW_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define BOOST5V_SW_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define BOOST5V_SW_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define BOOST5V_SW_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define BOOST5V_SW_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define BOOST5V_SW_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
// get/set IO_RC4 aliases
#define CHARGE_LED_RED_TRIS                 TRISCbits.TRISC4
#define CHARGE_LED_RED_LAT                  LATCbits.LATC4
#define CHARGE_LED_RED_PORT                 PORTCbits.RC4
#define CHARGE_LED_RED_WPU                  WPUCbits.WPUC4
#define CHARGE_LED_RED_OD                   ODCONCbits.ODCC4
#define CHARGE_LED_RED_ANS                  ANSELCbits.ANSC4
#define CHARGE_LED_RED_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define CHARGE_LED_RED_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define CHARGE_LED_RED_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define CHARGE_LED_RED_GetValue()           PORTCbits.RC4
#define CHARGE_LED_RED_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define CHARGE_LED_RED_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define CHARGE_LED_RED_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define CHARGE_LED_RED_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define CHARGE_LED_RED_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define CHARGE_LED_RED_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define CHARGE_LED_RED_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define CHARGE_LED_RED_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)
// get/set IO_RC5 aliases
#define BOOST_5V_IN_TRIS                 TRISCbits.TRISC5
#define BOOST_5V_IN_LAT                  LATCbits.LATC5
#define BOOST_5V_IN_PORT                 PORTCbits.RC5
#define BOOST_5V_IN_WPU                  WPUCbits.WPUC5
#define BOOST_5V_IN_OD                   ODCONCbits.ODCC5
#define BOOST_5V_IN_ANS                  ANSELCbits.ANSC5
#define BOOST_5V_IN_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define BOOST_5V_IN_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define BOOST_5V_IN_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define BOOST_5V_IN_GetValue()           PORTCbits.RC5
#define BOOST_5V_IN_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define BOOST_5V_IN_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define BOOST_5V_IN_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define BOOST_5V_IN_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define BOOST_5V_IN_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define BOOST_5V_IN_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define BOOST_5V_IN_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define BOOST_5V_IN_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)
#define RC5_SetInterruptHandler  BOOST_5V_IN_SetInterruptHandler
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the BOOST_5V_IN pin functionality
 * @param none
 * @return none
 */
void BOOST_5V_IN_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for BOOST_5V_IN pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for BOOST_5V_IN at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void BOOST_5V_IN_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for BOOST_5V_IN pin.
 *        This is a dynamic interrupt handler to be used together with the BOOST_5V_IN_SetInterruptHandler() method.
 *        This handler is called every time the BOOST_5V_IN ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*BOOST_5V_IN_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for BOOST_5V_IN pin. 
 *        This is a predefined interrupt handler to be used together with the BOOST_5V_IN_SetInterruptHandler() method.
 *        This handler is called every time the BOOST_5V_IN ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void BOOST_5V_IN_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/