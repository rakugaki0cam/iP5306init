/*
 * File:   iP5306v2.c
 * Comments: PIC16F18326
 * 
 * iP5306　リチウムイオンバッテリ充電、保護、5Vブースト出力、スイッチ　　I2C
 * 
 * メインスイッチ、スリープ
 * 
 * BatV - 3.3V convert  I2C
 * 
 * Revision history: 
 * 2024.01.03
 * v2_edition
 * 2024.01.22
 * 
 */
#include "iP5306v2.h"


#define IP5306_SLAVE_ID     0x75    //iP5306 Li battery charger & booster
//register
//system
#define REG_SYS_CTL0        0x00
#define REG_SYS_CTL1        0x01
#define REG_SYS_CTL2        0x02
//charge
#define REG_CHG_CTL0        0x20
#define REG_CHG_CTL1        0x21
#define REG_CHG_CTL2        0x22
#define REG_CHG_CTL3        0x23
//charge current
#define REG_CHG_DIG_CTL0    0x24
//status
#define REG_READ0           0x70
#define REG_READ1           0x71
#define REG_READ2           0x72
#define REG_READ3           0x77
#define REG_READ4           0x78
//
#define     ERROR   1
#define     OK      0


//Global
power_saving_mask_t sleepStat = POWERSAVING_NORMAL;


//***** iP5306 *****************************************************************
bool ip5306_init(void){
    //I2C iP5306 init
#define DEBUG5306
     
    uint8_t txData[4];
    uint8_t rxData[3] = {0, 0, 0};
    uint8_t waitCnt;
    
    //REG_SYS_CTL0                  //default 0x35 -> 0x31
    uint8_t boost = 0b1;            //[bit5]ブースト出力     1:する, 0:しない 
    uint8_t charge = 0b1;           //[bit4]充電機能        1:有効, 0:無効,
    uint8_t autoOn = 0b0;           //[bit2]オートオン      1:する, 0:しない       ----*
    uint8_t alwaysBoost = 0b0;      //[bit1]常時ブースト     0:しない, 1:オン
    uint8_t pushSwOff = 0b1;        //[bit0]プッシュSWオフ   1:可, 0:不可
    //REG_SYS_CTL1                  //default 0x1D -> 0xD9
    uint8_t boostLongPush = 0b1;    //[bit7]ブーストオフ     0:ダブル, 1:長押し     ----*
    uint8_t leddoubleclick = 0b1;   //[bit6]LEDライト       0:長押し, 1:ダブル押し ----* 
    uint8_t shortPushOff = 0b0;     //[bit5]短押しオフ       0:しない, 1:する
    uint8_t usbCutBoost = 0b0;      //[bit2]USB抜時ブースト出力 1:オン, 0:オフ　 (注.瞬停してしまう)
    uint8_t lowVoltage = 0b1;       //[bit0]3V以下オフ       1:する　0:そのまま 
    //REG_SYS_CTL2                  //default 0x64 -> 0x74
    uint8_t longPushTime = 0b1;     //[bit4]長押し時間 　　　　0:2sec, 1:3sec      ----*
    uint8_t autoOffTime = 0b01;     //[bit3:2]オートオフ時間  01:32sec, 00:8s, 10:16s, 11:64s
    
    //デフォルト値の読み出し
    printf("iP5306 init ...");
    txData[0] = REG_SYS_CTL0;
    if (!I2C1_Host.WriteRead(IP5306_SLAVE_ID, txData, 1, rxData, 3)){
        printf("I2C bus busy!\n");
        return ERROR;
    }
    waitCnt = 100;                                                                                        
    while (I2C1_Host.IsBusy() && waitCnt){
        waitCnt--;              
    }
    //printf("wait:%d \n", waitCnt);      //実測値98 なので実際は2しかカウントされない 
    if (I2C1_Host.ErrorGet() != I2C_ERROR_NONE){
        printf("I2C write read error!\n");
    }
    
    if ((rxData[0] | rxData[1] | rxData[2]) == 0){
        printf("I2C read error!\n");
        return ERROR;
    }
    
#ifdef DEBUG5306
    printf("\n(I2C 0x%02X reg 0x%02X\n", IP5306_SLAVE_ID, REG_SYS_CTL0);
    printf("read  %02X %02X %02X) \n", rxData[0], rxData[1], rxData[2]);
#endif

    //iP5306 initialize
    txData[0] = REG_SYS_CTL0;
    txData[1] = (uint8_t)(boost << 5) + (uint8_t)(charge << 4) + (uint8_t)(autoOn << 2) + (uint8_t)(alwaysBoost << 1) + pushSwOff;   
    txData[2] = (uint8_t)(boostLongPush << 7) + (uint8_t)(leddoubleclick << 6) + (uint8_t)(shortPushOff << 5) + (uint8_t)(usbCutBoost << 2) + lowVoltage;
    txData[3] = (uint8_t)(longPushTime << 4) + (uint8_t)(autoOffTime << 2);
    if (!I2C1_Host.Write(IP5306_SLAVE_ID, txData, 4)){
        printf("I2C bus busy!\n");
        return ERROR;
    }
    waitCnt = 100;                                                                                          
    while (I2C1_Host.IsBusy() && waitCnt){
        waitCnt--;              
    }
    //printf("wait:%d...", waitCnt);
    if (I2C1_Host.ErrorGet() != I2C_ERROR_NONE){
        printf("I2C write error!\n");
    }
    
#ifdef DEBUG5306
    //printf("(I2C 0x%02X reg 0x%02X\n", IP5306_SLAVE_ID, txData[0]);
    printf("write %02X %02X %02X) \n", txData[1], txData[2], txData[3]);
#endif
    
    printf("OK\n");
    return OK;
}


bool ip5306_ReadStatus(void){
    //I2C read
    //ret  0:OK, 1:ERROR

#define DEBUG5306_2//_no
    
    uint8_t txData[1];
    uint8_t rxData[2] = {0, 0};
    uint8_t waitCnt;
    uint8_t chargeEnable;
    uint8_t chargeStatus;
    uint8_t batLevel;
    uint8_t batPercent = 100;   //%
    static bool    usbinFlag = 0;

    /*
    if (IP5306_IRQ_PORT == 0){
       //iP5306 ONの確認
       printf("BOOST 5V off \n");
       CHARGE_LED_RED_SetHigh();   //赤LED点灯 -> エラー
       return ERROR;
    }
    */
    
    txData[0] = REG_READ0;
    if (!I2C1_Host.WriteRead(IP5306_SLAVE_ID, txData, 1, rxData, 2)){
        printf("I2C bus busy!\n");
        return ERROR;
    }
    waitCnt = 100;                                                                                         
    while (I2C1_Host.IsBusy() && waitCnt){
        waitCnt--;              
    }
    if (I2C1_Host.ErrorGet() != I2C_ERROR_NONE){
        printf("I2C write read error!\n");
    }
    chargeEnable = rxData[0];
    chargeStatus = rxData[1];
    //
    txData[0] = REG_READ4;
    if (!I2C1_Host.WriteRead(IP5306_SLAVE_ID, txData, 1, rxData, 1)){
        printf("I2C bus busy!\n");
        return ERROR;
    }
    waitCnt = 100;                                                                                         
    while (I2C1_Host.IsBusy() && waitCnt){
        waitCnt--;              
    }
    if (I2C1_Host.ErrorGet() != I2C_ERROR_NONE){
        printf("I2C write read error!\n");
    }
    batLevel = rxData[0];

    //BAT level 
    if (batLevel & 0b10000000){
        batPercent = 75;
    }
    if (batLevel & 0b01000000){
        batPercent = 50;
    }
    if (batLevel & 0b00100000){
        batPercent = 25;
    }
#ifdef  DEBUG5306_2
    printf("Bat:%3d%% ", batPercent);
#endif
    
#define DEBUG5306_3_no
#ifdef  DEBUG5306_3
    printf("READ0 0x70 cE %02X\n", chargeEnable);
    printf("READ1 0x71 cS %02X\n", chargeStatus);
    printf("READ4 0x78 bV %02X\n", batLevel);
    printf("\n");
#endif
    
    if (batLevel & 0b00010000){
        printf("batV < 3.2V \n");
    }
    if (batLevel & 0b00000010){
        printf("batV < 3.0V \n");
    }

    //Charge status change
    if (chargeEnable & 0b00001000){
        //USB IN
        if (usbinFlag == 0){
#ifdef  DEBUG5306_2
            printf("USB IN\n");
            __delay_ms(1);
#endif      
            usbinFlag = 1;
        }
    }else{
        CHARGE_LED_RED_SetLow();
        if (usbinFlag == 1){
#ifdef  DEBUG5306_2
            printf("USB Out\n");
            __delay_ms(1);
#endif
        }
        usbinFlag = 0;
    }

    if (usbinFlag == 1){
        //USB接続
        if (chargeStatus & 0b00001000){
            //充電完了 -> ディープスリープ
#ifdef  DEBUG5306_2
            printf("FULL\n");
            __delay_ms(1);
#endif
            CHARGE_LED_RED_SetLow();
            if (POWERSAVING_SLEEP == sleepStat){
                deepSleep();
                
                //------------- DEEP SLEEP -------------------------------------
                
            }
            
        }else{
            //充電中
#ifdef  DEBUG5306_2
            printf("Charging\n");
            __delay_ms(1);
#endif
            CHARGE_LED_RED_SetHigh();
        }
    }else{
#ifdef  DEBUG5306_2
            printf("discharging\n");
            __delay_ms(1);
#endif
    }   //usbinFlag
    
    return OK;
}


void ip5306_reset(void){
    //iP5306　I2C通信不良の時リセットする
    ip5306_off();
    __delay_ms(2);
    ip5306_on();
}


