/*
 * File:   header.h
 * 
 * ip5306init
 * 
 * 2024.01.22
 * 
 */

#ifndef _HEADER_H    /* Guard against multiple inclusion */
#define _HEADER_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "mcc_generated_files/system/system.h"

#include "iP5306v2.h"


void    mainSwOn_callback(void);

//main switch
void    mainSwPush(void);
//
void    awake(void);
void    intervalSleep(void);
void    deepSleep(void);
void    resetRestart(void);



#endif //_HEADER_H

/* *****************************************************************************
 End of File
 */
