/*******************************************************************************
* File Name: AF.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "AF.h"

static AF_BACKUP_STRUCT  AF_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: AF_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet AF_SUT.c usage_AF_Sleep_Wakeup
*******************************************************************************/
void AF_Sleep(void)
{
    #if defined(AF__PC)
        AF_backup.pcState = AF_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            AF_backup.usbState = AF_CR1_REG;
            AF_USB_POWER_REG |= AF_USBIO_ENTER_SLEEP;
            AF_CR1_REG &= AF_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(AF__SIO)
        AF_backup.sioState = AF_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        AF_SIO_REG &= (uint32)(~AF_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: AF_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to AF_Sleep() for an example usage.
*******************************************************************************/
void AF_Wakeup(void)
{
    #if defined(AF__PC)
        AF_PC = AF_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            AF_USB_POWER_REG &= AF_USBIO_EXIT_SLEEP_PH1;
            AF_CR1_REG = AF_backup.usbState;
            AF_USB_POWER_REG &= AF_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(AF__SIO)
        AF_SIO_REG = AF_backup.sioState;
    #endif
}


/* [] END OF FILE */
