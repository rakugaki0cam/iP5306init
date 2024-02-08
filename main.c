 /*
  * file:  main.c
  * 
  * iP5306 リチウムバッテリー充電モジュール設定用PIC
  *  PIC16F18326 14pin
  *     Vdd = バッテリー電圧(約3~4.2V)
  * 
  *     EUSART          - pin3  TX  debugger serial
  * 
  *     IP5306_IRQ      - pin5  RC5 Input IRQ.rise edge  P.D.100k
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
  * 2024.02.04  ver.1.00    とりあえず動作オッケー
  * 2024.02.08  ver.1.01    7秒長押しでリセット動作
  * 
  * 
  * 
  */
 
#include "header.h"


/*
    Main application
*/

bool mainSwFlag = 0;        //メインスイッチ割込
bool boostIRQflag = 0;      //Boost 5V output status

void mainSwOn_callback(void){
    mainSwFlag = 1;
}

void iP5306_irq_callback(void){
    //ブースト5V出力信号
    boostIRQflag = 1;
}

int main(void){
    uint8_t cnt;
    
    SYSTEM_Initialize();

    INT_SetInterruptHandler(mainSwOn_callback);
    IP5306_IRQ_SetInterruptHandler(iP5306_irq_callback);

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
    
    VREGCONbits.VREGPM = 1; //1:Low power sleep..wakeup slower.
    WDTCONbits.SWDTEN = 1;  //Watch Dog Timer:ON
    
    __delay_ms(500);
    
    printf("\n\n");
    printf("******************\n");
    printf(" iP5306 init\n");
    printf("       2024.02\n");
    printf("******************\n");
    printf("\n");

    //IP5306_ON_SetLow();    //iP5306をPICから強制的にオンする
    //__delay_ms(80);
    //IP5306_ON_SetHigh();    //iP5306をPICから強制的にオンする

    
    if(ip5306_Init()){
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
    
    // main loop ------------------------
    while(1){
        if (boostIRQflag == 1){
            __delay_ms(5);
            if (IP5306_IRQ_PORT == 1){
                printf("boost 5V on \n");
                awake();
            }
        }
        
        if (IP5306_IRQ_PORT == 0){
            printf("IRQ Low...");
            if(ip5306_Init()){
                //error = ip5306がOFF
                printf("BOOST OFF confirm\n");
                deepSleep();
                //---------------- S L E E P ------------------------------------
            
                awake();
            }else{
                //OK = ip5306はオンしていてI2Cの設定ができた
                printf("iP5306 I2C Ok\n");
            }
        }
        
        ip5306_ReadStatus();

        
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
    boostIRQflag = 0;
}


//--- SLEEP -----
void intervalSleep(void){
    //PICは充電ステータスで充電完了をチェックする。
    sleepStat = POWERSAVING_SLEEP;
    BOOST5V_SW_SetLow();                //5V OUTPUT LoadSwitchオフ
    WDTCONbits.SWDTEN = 1;
    printf("\n5V loadSW off\n");  //充電完了待ち状態へ節電
    if (IP5306_IRQ_PORT == 1){
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


