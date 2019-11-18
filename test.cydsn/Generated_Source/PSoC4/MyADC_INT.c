/*******************************************************************************
* File Name: MyADC_INT.c
* Version 2.50
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MyADC.h"
#include "cyapicallbacks.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(MyADC_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: MyADC_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( MyADC_ISR )
    {
        uint32 intr_status;

        /* Read interrupt status register */
        intr_status = MyADC_SAR_INTR_REG;

        #ifdef MyADC_ISR_INTERRUPT_CALLBACK
            MyADC_ISR_InterruptCallback();
        #endif /* MyADC_ISR_INTERRUPT_CALLBACK */


        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
        /* `#START MAIN_ADC_ISR`  */

        /* `#END`  */
        
        /* Clear handled interrupt */
        MyADC_SAR_INTR_REG = intr_status;
    }

#endif   /* End MyADC_IRQ_REMOVE */


/* [] END OF FILE */
