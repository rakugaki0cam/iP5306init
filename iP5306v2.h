/*
 * File:   iP5306v2.h
 * 
 * 2024.01.03
 * v2_edition
 * 2024.01.22
 * 
 * 
 */

#ifndef _IP5306_H    /* Guard against multiple inclusion */
#define _IP5306_H


//Global
typedef enum
{
    POWERSAVING_NORMAL = 0,
    POWERSAVING_SLEEP  = 1,
    POWERSAVING_DEEPSLEEP = 2,
} power_saving_mask_t;

extern power_saving_mask_t sleepStat;



//iP5306
bool    ip5306_Init(void);
bool    ip5306_ReadStatus(void);

//main switch
void    mainSwPush(void);



#endif //_IP5306_H


/* *****************************************************************************
 End of File
 */
