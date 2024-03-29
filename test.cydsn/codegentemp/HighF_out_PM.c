/*******************************************************************************
* File Name: HighF_out.c  
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
#include "HighF_out.h"

static HighF_out_BACKUP_STRUCT  HighF_out_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HighF_out_Sleep
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
*  \snippet HighF_out_SUT.c usage_HighF_out_Sleep_Wakeup
*******************************************************************************/
void HighF_out_Sleep(void)
{
    #if defined(HighF_out__PC)
        HighF_out_backup.pcState = HighF_out_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HighF_out_backup.usbState = HighF_out_CR1_REG;
            HighF_out_USB_POWER_REG |= HighF_out_USBIO_ENTER_SLEEP;
            HighF_out_CR1_REG &= HighF_out_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HighF_out__SIO)
        HighF_out_backup.sioState = HighF_out_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HighF_out_SIO_REG &= (uint32)(~HighF_out_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HighF_out_Wakeup
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
*  Refer to HighF_out_Sleep() for an example usage.
*******************************************************************************/
void HighF_out_Wakeup(void)
{
    #if defined(HighF_out__PC)
        HighF_out_PC = HighF_out_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HighF_out_USB_POWER_REG &= HighF_out_USBIO_EXIT_SLEEP_PH1;
            HighF_out_CR1_REG = HighF_out_backup.usbState;
            HighF_out_USB_POWER_REG &= HighF_out_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HighF_out__SIO)
        HighF_out_SIO_REG = HighF_out_backup.sioState;
    #endif
}


/* [] END OF FILE */
