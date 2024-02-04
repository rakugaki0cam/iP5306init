 /*
  * file:  main.c
  * 
  * iP5306 リチウムバッテリー充電モジュール設定用PIC
  *  PIC16F18326 14pin
  *     Vdd = バッテリー電圧(約3~4.2V)
  * 
  *     EUSART          - pin3  TX  debugger serial
  * 
  *     BOOST_5V_IN     - pin5  RC5 Input IOC.positive
  *     CHARGE_LED_RED  - pin6  RC4 Output
  *     BOOST5V_SW      - pin7  RC3 Output
  *     MAIN_SW         - pin11 RA2 ext_INT P.U. Fall edge
  * 
  *     MSSP1 I2C       - pin9  SDA1
  *     MSSP1 I2C       - pin10 SCL1
  * 
  *     picはバッテリーに直接つなぐので電源は切れない。スリープで対応。実測15uAくらい。
  * 
  * 
  * 
  * 2024.01.22
  * 
  */
 
#include "header.h"


/*
    Main application
*/

bool mainSwFlag = 0;        //メインスイッチ割込
bool boost5VoltFlag = 0;    //Boost 5V output signal

void mainSwOn_callback(void){
    mainSwFlag = 1;
}

void boost5Vin_callback(void){
    //ブースト5V出力信号
    boost5VoltFlag = 1;
}

int main(void){
    uint8_t cnt;
    
    SYSTEM_Initialize();

    INT_SetInterruptHandler(mainSwOn_callback);
    BOOST_5V_IN_SetInterruptHandler(boost5Vin_callback);

    BOOST5V_SW_SetHigh();   //5V OUTPUT LoadSwitchオン

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    __delay_ms(500);
    
    printf("\n\n");
    printf("******************\n");
    printf(" iP5306 init\n");
    printf("       2024.02\n");
    printf("******************\n");
    printf("\n");

    ip5306_Init();
    /*
    cnt = 5;
    while (ip5306_Init()){
        __delay_ms(1000);
        cnt--;
        if (cnt <= 0){
            printf("I2C Error!\n");
            BOOST5V_SW_SetLow();        //5V OUTPUT LoadSwitchオフ
            CHARGE_LED_RED_SetHigh();   //赤LED点灯 -> エラー
            sleepStat = POWERSAVING_DEEPSLEEP;
            WDTCONbits.SWDTEN = 0;      //WDTでのスリープ解除なし
            printf("---DEEP SLEEP-----\n");
            __delay_ms(500);
            SLEEP();                    //スリープ
    
            ///////////////////////// DEEP SLEEP //////////////////////////////////////////////////
    
            NOP();
            NOP();
            resetRestart();
        }
    }
    */
    
    VREGCONbits.VREGPM = 1; //1:Low power sleep..wakeup slower.
    WDTCONbits.SWDTEN = 1;  //Watch Dog Timer:ON
    
    while(1){
        if (boost5VoltFlag == 1){
            printf("boost 5V on \n");
            awake();
        }
        
        if (BOOST_5V_IN_PORT == 0){
            printf("BOOST 5V off \n");
            deepSleep();
            //---------------- S L E E P ------------------------------------
            
            
            resetRestart();
            //awake();//???????????????????????
        }
        
        ip5306_ReadStatus();

        /*
        cnt = 5;
        while (ip5306_ReadStatus()){
            __delay_ms(1000);
            cnt--;
            if (cnt <= 0){
                printf("I2C Error!\n");
                CHARGE_LED_RED_SetHigh();   //赤LED点灯 -> エラー
                sleepStat = POWERSAVING_DEEPSLEEP;
                WDTCONbits.SWDTEN = 0;      //WDTでのスリープ解除なし
                printf("---DEEP SLEEP-----\n");
                __delay_ms(500);
                SLEEP();                    //スリープ

                ///////////////////////// DEEP SLEEP //////////////////////////////////////////////////

                NOP();
                NOP();
                resetRestart();
            }
        }
        */
        
        //printf("interval sleep in \n\n");
        SLEEP();
        //---------- SLEEP ---------------
        //wake....  WDT interval 4sec
        //          INT mainSW push
        //          IOC Boost5Vout signal
        
        NOP();
        NOP();
        
        if (mainSwFlag){
            mainSwPush();
            mainSwFlag = 0;
        }
        
    }    
}


//--- WAKE -----
void awake(void){
    printf("wake\n");
    sleepStat = POWERSAVING_NORMAL; 
    __delay_ms(1000);
    BOOST5V_SW_SetHigh();   //5V OUTPUT LoadSwitchオン
    ip5306_Init();
    WDTCONbits.SWDTEN = 1;
    boost5VoltFlag = 0;
}


//--- SLEEP -----
void intervalSleep(void){
    //PICは充電ステータスで充電完了をチェックする。
    sleepStat = POWERSAVING_SLEEP;
    BOOST5V_SW_SetLow();                //5V OUTPUT LoadSwitchオフ
    WDTCONbits.SWDTEN = 1;
    printf("\nboost SW off\n");  //充電完了待ち状態へ節電
    if (BOOST_5V_IN_PORT == 1){
        //boost5V出力中 = USB 5V IN 充電中　
        printf("wait to FullCharge \n");
    }
    printf("\n");
}

    
void deepSleep(void){
    //充電完了時にはPICを完全スリープに
    sleepStat = POWERSAVING_DEEPSLEEP;
    printf("---DEEP SLEEP-----\n");
    BOOST5V_SW_SetLow();        //5V OUTPUT LoadSwitchオフ
    CHARGE_LED_RED_SetLow();
    WDTCONbits.SWDTEN = 0;      //WDTでのスリープ解除なし
    __delay_ms(500);
    SLEEP();                    //スリープ
    
    ///////////////////////// DEEP SLEEP //////////////////////////////////////////////////
    
    NOP();
    NOP();
}


//--- RESET -----
void resetRestart(void){
    __delay_ms(200);
    printf("\n");
    printf("***** ReSTART! *****\n");
    __delay_ms(500);
    RESET();       //ソフトウエアリセット
    
}


