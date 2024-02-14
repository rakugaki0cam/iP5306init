 /*
  * file:  main.c
  * 
  * iP5306 ���`�E���o�b�e���[�[�d���W���[���ݒ�pPIC
  *  PIC16F18326 14pin
  *     Vdd = �o�b�e���[�d��(��3~4.2V)
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
  *     pic�̓o�b�e���[�ɒ��ڂȂ��̂œd���͐؂�Ȃ��B�X���[�v�őΉ��B����15uA���炢�B
  * 
  * 
  * 
  * 2024.01.22
  * 
  * 2024.02.04  ver.1.00    �Ƃ肠��������I�b�P�[
  * 2024.02.08  ver.1.01    7�b�������Ń��Z�b�g����
  * 2024.02.14  ver.1.02    git��������̕����|�C���g�Ƃ��č쐬
  * 
  * 
  */
 
#include "header.h"


//���C���X�C�b�`�������
#define     MAIN_SW_PUSH    !MAIN_SW_PORT

/*
    Main application
*/

bool mainSwFlag = 0;        //���C���X�C�b�`����
bool boostIRQflag = 0;      //Boost 5V output status

void mainSwOn_callback(void){
    mainSwFlag = 1;
}

void iP5306_irq_callback(void){
    //�u�[�X�g5V�o�͐M��
    boostIRQflag = 1;
}

int main(void){
    uint8_t cnt;
    
    SYSTEM_Initialize();

    INT_SetInterruptHandler(mainSwOn_callback);
    IP5306_IRQ_SetInterruptHandler(iP5306_irq_callback);

    BOOST5V_SW_SetHigh();   //5V OUTPUT LoadSwitch�I��

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

    //IP5306_ON_SetLow();    //iP5306��PIC���狭���I�ɃI������
    //__delay_ms(80);
    //IP5306_ON_SetHigh();    //iP5306��PIC���狭���I�ɃI������

    
    while(MAIN_SW_PUSH);
    
    ip5306_Init();
    
    
    // main loop ------------------------
    while(1){
        if (boostIRQflag == 1){
            //rise edge
            __delay_ms(5);
            if (IP5306_IRQ_PORT == 1){
                printf("boost 5V on \n");
                awake();
            }
        }
        
        if (IP5306_IRQ_PORT == 0){
            printf("IRQ Low...");
            if(ip5306_Init()){
                //error = ip5306��OFF
                printf("BOOST OFF confirm\n");
                deepSleep();
                //---------------- S L E E P ------------------------------------
            
                //awake();
            }else{
                //OK = ip5306�̓I�����Ă���I2C�̐ݒ肪�ł���
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
        
        CLRWDT();                   //�E�H�b�`�h�b�N�^�C�}�@�N���A 

    }    
}



//***** main switch ************************************************************

void mainSwPush(void){
    //���C���X�C�b�`�������ꂽ��
    uint8_t sleep_sw_timer = 0;

    __delay_ms(50);      //�`���^�����O�΍�
    if(MAIN_SW_PUSH){
        printf("mainSW ON\n");
        //if (POWERSAVING_NORMAL == sleepStat){
            //�X���[�v���łȂ����͒���������
            //�[�d���̒������ł݂������̃X���[�v��Ԃɂ���
            sleep_sw_timer = 0;
            while(MAIN_SW_PUSH){
                //��������
                __delay_ms(50);
                CLRWDT();                   //�E�H�b�`�h�b�N�^�C�}�@�N���A 
                printf(".");
                sleep_sw_timer++;
                
                if (IP5306_IRQ_PORT == 0){
                    //USB�A�E�g�̎��A�������Ń^�[�Q�b�g���I�t������
                    while(MAIN_SW_PUSH){
                        //�{�^���𗣂��܂ő҂�
                        CLRWDT();
                    }
                    __delay_ms(50);
                    deepSleep();
                    //--------------sleep-------
                    resetRestart();         //���Z�b�g�ċN��

                }
                if (sleep_sw_timer > 60){       //3�b
                    sleepStat = POWERSAVING_SLEEP;
                    intervalSleep();        //�C���^�[�o���X���[�v
                    return;
                }
            }
            
            if (POWERSAVING_SLEEP == sleepStat){
                //USBi�C��=�[�d���̎��̓^�[�Q�b�g���I������
                awake();
            }
            
            
            
        //}else{
        //    //�X���[�v�A�f�B�[�v�X���[�v���Ȃ�
        //    awake();
        //}
    }
}



//--- WAKE -----
void awake(void){
    printf("wake\n");
    sleepStat = POWERSAVING_NORMAL; 
    __delay_ms(1000);
    BOOST5V_SW_SetHigh();   //5V OUTPUT LoadSwitch�I��
    ip5306_Init();
    WDTCONbits.SWDTEN = 1;
    boostIRQflag = 0;
}


//--- SLEEP -----
void intervalSleep(void){
    //PIC�͏[�d�X�e�[�^�X�ŏ[�d�������`�F�b�N����B
    sleepStat = POWERSAVING_SLEEP;
    BOOST5V_SW_SetLow();                //5V OUTPUT LoadSwitch�I�t
    WDTCONbits.SWDTEN = 1;
    printf("\n5V loadSW off\n");  //�[�d�����҂���Ԃ֐ߓd
    if (IP5306_IRQ_PORT == 1){
        //boost5V�o�͒� = USB 5V IN �[�d���@
        printf("wait to FullCharge \n");
    }
    printf("\n");
}

    
void deepSleep(void){
    //�[�d�������ɂ�PIC�����S�X���[�v��
    sleepStat = POWERSAVING_DEEPSLEEP;
    printf("---DEEP SLEEP-----\n");
    BOOST5V_SW_SetLow();        //5V OUTPUT LoadSwitch�I�t
    CHARGE_LED_RED_SetLow();
    WDTCONbits.SWDTEN = 0;      //WDT�ł̃X���[�v�����Ȃ�
    __delay_ms(500);
    SLEEP();                    //�X���[�v
    
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
    RESET();       //�\�t�g�E�G�A���Z�b�g
    
}


