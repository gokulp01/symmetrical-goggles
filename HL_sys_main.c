/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_sys_core.h"
#include "HL_mibspi.h"
#include "HL_esm.h"
#include "HL_rti.h"
#include "HL_gio.h"
#include "HL_het.h"
#include "HL_sci.h"
#include "HL_eqep.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */


//unsigned char command[8];
long countR=0, countL=0, oldCountL=0, oldCountR=0;
char start_token = '[', end_token = ']', reg[10];



/* USER CODE END */

int main(void)
    {
/* USER CODE BEGIN (3) */

       rtiInit();
       hetInit();
       sciInit();
       QEPInit();

       rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);
        _enable_interrupt_();
        _enable_IRQ();
        rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);


       eqepEnableCounter(eqepREG2);
       eqepEnableUnitTimer(eqepREG2);
       eqepEnableCapture(eqepREG2);
       eqepEnableCounter(eqepREG1);
       eqepEnableUnitTimer(eqepREG1);
       eqepEnableCapture(eqepREG1);

        while(1)
        {


        }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{

    uint32_t NumberOfChars;
    float velocityL=0,velocityR=0;
    if((eqepREG2->QEPSTS & 0x80U) !=0U)
           {
                countR=eqepREG2->QPOSLAT;
                eqepREG2->QEPSTS |= 0x80U;
           }

    if((eqepREG1->QEPSTS & 0x80U) !=0U)
    {
       countL = eqepREG1->QPOSLAT;
       eqepREG1->QEPSTS |= 0x80U;
   }

  //  velocityL = ((float) (countL-oldCountL)*0.070685);
   // velocityR = ((float)  (countR-oldCountR)*0.070685);
    velocityL = 10.5;
            velocityR = 20.60;
            printf("%d\n",sizeof(velocityL));

         oldCountR = countR;
         oldCountL = countL;
         memcpy(reg, &start_token, 1);
         memcpy(reg+1, &velocityL, 4);
         memcpy(reg+5, &velocityR, 4);
         memcpy(reg+9, &end_token, 1);

  sciSend(sciREG1, 10, reg);
}
/* USER CODE END */
