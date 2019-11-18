/*******************************************************************************
* File Name: MyADC_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MyADC.h"


/***************************************
* Local data allocation
***************************************/

static MyADC_BACKUP_STRUCT  MyADC_backup =
{
    MyADC_DISABLED,
    0u    
};


/*******************************************************************************
* Function Name: MyADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MyADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MyADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MyADC_backup - modified.
*
*******************************************************************************/
void MyADC_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    MyADC_backup.dftRegVal = MyADC_SAR_DFT_CTRL_REG & (uint32)~MyADC_ADFT_OVERRIDE;
    MyADC_SAR_DFT_CTRL_REG |= MyADC_ADFT_OVERRIDE;
    if((MyADC_SAR_CTRL_REG  & MyADC_ENABLE) != 0u)
    {
        if((MyADC_SAR_SAMPLE_CTRL_REG & MyADC_CONTINUOUS_EN) != 0u)
        {
            MyADC_backup.enableState = MyADC_ENABLED | MyADC_STARTED;
        }
        else
        {
            MyADC_backup.enableState = MyADC_ENABLED;
        }
        MyADC_StopConvert();
        MyADC_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((MyADC_SAR_CTRL_REG & MyADC_BOOSTPUMP_EN) != 0u)
        {
            MyADC_SAR_CTRL_REG &= (uint32)~MyADC_BOOSTPUMP_EN;
            MyADC_backup.enableState |= MyADC_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        MyADC_backup.enableState = MyADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: MyADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MyADC_backup - used.
*
*******************************************************************************/
void MyADC_Wakeup(void)
{
    MyADC_SAR_DFT_CTRL_REG = MyADC_backup.dftRegVal;
    if(MyADC_backup.enableState != MyADC_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((MyADC_backup.enableState & MyADC_BOOSTPUMP_ENABLED) != 0u)
        {
            MyADC_SAR_CTRL_REG |= MyADC_BOOSTPUMP_EN;
        }
        MyADC_Enable();
        if((MyADC_backup.enableState & MyADC_STARTED) != 0u)
        {
            MyADC_StartConvert();
        }
    }
}
/* [] END OF FILE */
