/*******************************************************************************
* File Name: MyADC.c
* Version 2.50
*
* Description:
*  This file provides the source code to the API for the Sequencing Successive
*  Approximation ADC Component Component.
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
* Global data allocation
***************************************/
uint8 MyADC_initVar = 0u;
volatile int16 MyADC_offset[MyADC_TOTAL_CHANNELS_NUM];
volatile int32 MyADC_countsPer10Volt[MyADC_TOTAL_CHANNELS_NUM];   /* Gain compensation */


/***************************************
* Local data allocation
***************************************/
/* Channels configuration generated by customiser */
static const uint32 CYCODE MyADC_channelsConfig[] = { 0x00000400u };


/*******************************************************************************
* Function Name: MyADC_Start
********************************************************************************
*
* Summary:
*  Performs all required initialization for this component
*  and enables the power. The power will be set to the appropriate
*  power based on the clock frequency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The MyADC_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  MyADC_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of MyADC_Start() routine, or the user may call
*  MyADC_Init() and MyADC_Enable() as done in the
*  MyADC_Start() routine.
*
*******************************************************************************/
void MyADC_Start(void)
{
    /* If not Initialized then initialize all required hardware and software */
    if(MyADC_initVar == 0u)
    {
        MyADC_Init();
        MyADC_initVar = 1u;
    }
    MyADC_Enable();
}


/*******************************************************************************
* Function Name: MyADC_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  MyADC_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The MyADC_offset variable is initialized.
*
*******************************************************************************/
void MyADC_Init(void)
{
    uint32 chNum;
    uint32 tmpRegVal;
    int32 counts;

    #if(MyADC_TOTAL_CHANNELS_NUM > 1u)
        static const uint8 CYCODE MyADC_InputsPlacement[] =
        {
            (uint8)(MyADC_cy_psoc4_sarmux_8__CH_0_PORT << 4u) |
            (uint8)MyADC_cy_psoc4_sarmux_8__CH_0_PIN
            ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_1_PORT << 4u) |
             (uint8)MyADC_cy_psoc4_sarmux_8__CH_1_PIN
            #if(MyADC_TOTAL_CHANNELS_NUM > 2u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_2_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_2_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 2u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 3u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_3_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_3_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 3u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 4u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_4_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_4_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 4u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 5u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_5_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_5_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 5u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 6u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_6_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_6_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 6u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 7u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_7_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_7_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 7u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 8u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_8_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_8_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 8u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 9u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_9_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_9_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 9u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 10u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_10_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_10_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 10u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 11u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_11_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_11_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 11u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 12u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_12_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_12_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 12u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 13u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_13_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_13_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 13u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 14u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_14_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_14_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 14u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 15u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_15_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_15_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 15u */
            #if(MyADC_TOTAL_CHANNELS_NUM > 16u)
                ,(uint8)(MyADC_cy_psoc4_sarmux_8__CH_16_PORT << 4u) |
                 (uint8)MyADC_cy_psoc4_sarmux_8__CH_16_PIN
            #endif /* End MyADC_TOTAL_CHANNELS_NUM > 16u */
        };
    #endif /* End MyADC_TOTAL_CHANNELS_NUM > 1u */

    #if(MyADC_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(MyADC_INTC_NUMBER, MyADC_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(MyADC_INTC_NUMBER, &MyADC_ISR);
    #endif   /* End MyADC_IRQ_REMOVE */

    /* Init SAR and MUX registers */
    MyADC_SAR_CHAN_EN_REG = MyADC_DEFAULT_EN_CHANNELS;
    MyADC_SAR_CTRL_REG |= MyADC_DEFAULT_CTRL_REG_CFG | 
        /* Enable the SAR internal pump when global pump is enabled */
        (((MyADC_PUMP_CTRL_REG & MyADC_PUMP_CTRL_ENABLED) != 0u) ? 
        MyADC_BOOSTPUMP_EN : 0u);
    MyADC_SAR_SAMPLE_CTRL_REG = MyADC_DEFAULT_SAMPLE_CTRL_REG_CFG;
    MyADC_SAR_RANGE_THRES_REG = MyADC_DEFAULT_RANGE_THRES_REG_CFG;
    MyADC_SAR_RANGE_COND_REG  = MyADC_COMPARE_MODE;
    MyADC_SAR_SAMPLE_TIME01_REG = MyADC_DEFAULT_SAMPLE_TIME01_REG_CFG;
    MyADC_SAR_SAMPLE_TIME23_REG = MyADC_DEFAULT_SAMPLE_TIME23_REG_CFG;
    
    /* Connect Vm to VSSA when even one channel is single-ended or multiple channels configured */
    #if(MyADC_DEFAULT_MUX_SWITCH0 != 0u)
        MyADC_MUX_SWITCH0_REG |= MyADC_DEFAULT_MUX_SWITCH0;
        /* Set MUX_HW_CTRL_VSSA in MUX_SWITCH_HW_CTRL when multiple channels enabled */
        #if(MyADC_TOTAL_CHANNELS_NUM > 1u)
            MyADC_MUX_SWITCH_HW_CTRL_REG |= MyADC_DEFAULT_MUX_SWITCH0;
        #endif /* MyADC_TOTAL_CHANNELS_NUM > 1u */
    #endif /*MyADC_CHANNELS_MODE !=0 */

    MyADC_SAR_SATURATE_INTR_MASK_REG = 0u;
    MyADC_SAR_RANGE_INTR_MASK_REG = 0u;
    MyADC_SAR_INTR_MASK_REG = MyADC_SAR_INTR_MASK;

    #if(MyADC_CY_SAR_IP_VER == MyADC_CY_SAR_IP_VER0)
        MyADC_ANA_TRIM_REG = MyADC_TRIM_COEF;
    #endif /* (MyADC_CY_SAR_IP_VER == MyADC_CY_SAR_IP_VER0) */

    /* Read and modify default configuration based on characterization */
    tmpRegVal = MyADC_SAR_DFT_CTRL_REG;
    tmpRegVal &= (uint32)~MyADC_DCEN;
    
    #if(MyADC_CY_SAR_IP_VER == MyADC_CY_SAR_IP_VER0)
        #if(MyADC_NOMINAL_CLOCK_FREQ > (MyADC_MAX_FREQUENCY / 2))
            tmpRegVal |= MyADC_SEL_CSEL_DFT_CHAR;
        #else  /* clock speed < 9 Mhz */
            tmpRegVal |= MyADC_DLY_INC;
        #endif /* clock speed > 9 Mhz */
    #else
        #if ((MyADC_DEFAULT_VREF_SEL == MyADC__INTERNAL1024) || \
             (MyADC_DEFAULT_VREF_SEL == MyADC__INTERNALVREF))
            tmpRegVal |= MyADC_DLY_INC;
        #else
            tmpRegVal |= MyADC_DCEN;
            tmpRegVal &= (uint32)~MyADC_DLY_INC;
        #endif /* ((MyADC_DEFAULT_VREF_SEL == MyADC__INTERNAL1024) || \
                   (MyADC_DEFAULT_VREF_SEL == MyADC__INTERNALVREF)) */
    #endif /* (MyADC_CY_SAR_IP_VER == MyADC_CY_SAR_IP_VER0) */
    
    MyADC_SAR_DFT_CTRL_REG = tmpRegVal;

    #if(MyADC_MAX_RESOLUTION != MyADC_RESOLUTION_12)
        MyADC_WOUNDING_REG = MyADC_ALT_WOUNDING;
    #endif /* MyADC_MAX_RESOLUTION != MyADC_RESOLUTION_12 */

    for(chNum = 0u; chNum < MyADC_TOTAL_CHANNELS_NUM; chNum++)
    {
        tmpRegVal = (MyADC_channelsConfig[chNum] & MyADC_CHANNEL_CONFIG_MASK);
        #if(MyADC_TOTAL_CHANNELS_NUM > 1u)
            tmpRegVal |= MyADC_InputsPlacement[chNum];
        #endif /* End MyADC_TOTAL_CHANNELS_NUM > 1u */
        
        
        /* When the part is limited to 10-bit then the SUB_RESOLUTION bit
        *  will be ignored and the RESOLUTION bit selects between 10-bit
        *  (0) and 8-bit (1) resolution.
        */
        #if((MyADC_MAX_RESOLUTION != MyADC_RESOLUTION_12) && \
            (MyADC_ALT_WOUNDING == MyADC_WOUNDING_10BIT))
            tmpRegVal &= (uint32)(~MyADC_ALT_RESOLUTION_ON);
        #endif /* MyADC_MAX_RESOLUTION != MyADC_RESOLUTION_12 */

        #if(MyADC_INJ_CHANNEL_ENABLED)
        if(chNum < MyADC_SEQUENCED_CHANNELS_NUM)
        #endif /* MyADC_INJ_CHANNEL_ENABLED */
        {
            CY_SET_REG32((reg32 *)(MyADC_SAR_CHAN_CONFIG_IND + (uint32)(chNum << 2)), tmpRegVal);

            if((MyADC_channelsConfig[chNum] & MyADC_IS_SATURATE_EN_MASK) != 0u)
            {
                MyADC_SAR_SATURATE_INTR_MASK_REG |= (uint16)((uint16)1 << chNum);
            }

            if((MyADC_channelsConfig[chNum] & MyADC_IS_RANGE_CTRL_EN_MASK) != 0u)
            {
                MyADC_SAR_RANGE_INTR_MASK_REG |= (uint16)((uint16)1 << chNum);
            }
        }
        #if(MyADC_INJ_CHANNEL_ENABLED)
            else
            {
                CY_SET_REG32(MyADC_SAR_INJ_CHAN_CONFIG_PTR, tmpRegVal | MyADC_INJ_TAILGATING);

                if((MyADC_channelsConfig[chNum] & MyADC_IS_SATURATE_EN_MASK) != 0u)
                {
                    MyADC_SAR_INTR_MASK_REG |= MyADC_INJ_SATURATE_MASK;
                }

                if((MyADC_channelsConfig[chNum] & MyADC_IS_RANGE_CTRL_EN_MASK) != 0u)
                {
                    MyADC_SAR_INTR_MASK_REG |= MyADC_INJ_RANGE_MASK;
                }
            }
        #endif /* MyADC_INJ_CHANNEL_ENABLED */

        if((MyADC_channelsConfig[chNum] & MyADC_ALT_RESOLUTION_ON) != 0u)
        {
               counts = (int32)MyADC_DEFAULT_MAX_WRK_ALT;
        }
        else
        {
               counts = (int32)MyADC_SAR_WRK_MAX_12BIT;
        }

        if((MyADC_channelsConfig[chNum] & MyADC_DIFFERENTIAL_EN) == 0u)
        {
            #if((MyADC_DEFAULT_SE_RESULT_FORMAT_SEL == MyADC__FSIGNED) && \
                (MyADC_DEFAULT_NEG_INPUT_SEL == MyADC__VREF))
                /* Set offset to the minus half scale to convert results to unsigned format */
                MyADC_offset[chNum] = (int16)(counts / -2);
            #else
                MyADC_offset[chNum] = 0;
            #endif /* end DEFAULT_SE_RESULT_FORMAT_SEL == MyADC__FSIGNED */
        }
        else    /* Differential channel */
        {
            #if(MyADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MyADC__FUNSIGNED)
                /* Set offset to the half scale to convert results to signed format */
                MyADC_offset[chNum] = (int16)(counts / 2);
            #else
                MyADC_offset[chNum] = 0;
            #endif /* end MyADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MyADC__FUNSIGNED */
        }
        /* Calculate gain in counts per 10 volts with rounding */
        MyADC_countsPer10Volt[chNum] = (int16)(((counts * MyADC_10MV_COUNTS) +
                            MyADC_DEFAULT_VREF_MV_VALUE) / (MyADC_DEFAULT_VREF_MV_VALUE * 2));
    }
}

/*******************************************************************************
* Function Name: ADC_SAR_1_Enable
********************************************************************************
*
* Summary:
*  Enables the clock and analog power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_Enable(void)
{
    if (0u == (MyADC_SAR_CTRL_REG & MyADC_ENABLE))
    {
        #if(MyADC_CY_SAR_IP_VER != MyADC_CY_SAR_IP_VER0)

            while (0u != (MyADC_SAR_STATUS_REG & MyADC_STATUS_BUSY))
            {
                /* wait for SAR to go idle to avoid deadlock */
            }
        #endif /* (MyADC_CY_SAR_IP_VER != MyADC_CY_SAR_IP_VER0) */
        
        MyADC_SAR_CTRL_REG |= MyADC_ENABLE;
        
        /* The block is ready to use 10 us after the enable signal is set high. */
        CyDelayUs(MyADC_10US_DELAY);         
    }
}


/*******************************************************************************
* Function Name: MyADC_Stop
********************************************************************************
*
* Summary:
*  This function stops ADC conversions and puts the ADC into its lowest power
*  mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_Stop(void)
{
    MyADC_SAR_CTRL_REG &= (uint32)~MyADC_ENABLE;
}


/*******************************************************************************
* Function Name: MyADC_StartConvert
********************************************************************************
*
* Summary:
*  Description:
*  For free running mode, this API starts the conversion process and it
*  runs continuously.
*
*  In a triggered mode, this routine triggers every conversion by
*  writing into the FW_TRIGGER bit in SAR_START_CTRL reg. In triggered mode,
*  every conversion has to start by this API.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_StartConvert(void)
{
    #if(MyADC_DEFAULT_SAMPLE_MODE_SEL == MyADC__FREERUNNING)
        MyADC_SAR_SAMPLE_CTRL_REG |= MyADC_CONTINUOUS_EN;
    #else /* Firmware trigger */
        MyADC_SAR_START_CTRL_REG = MyADC_FW_TRIGGER;
    #endif /* End MyADC_DEFAULT_SAMPLE_MODE == MyADC__FREERUNNING */

}


/*******************************************************************************
* Function Name: MyADC_StopConvert
********************************************************************************
*
* Summary:
*  Forces the ADC to stop all conversions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_StopConvert(void)
{
    #if(MyADC_DEFAULT_SAMPLE_MODE_SEL == MyADC__FREERUNNING)
        MyADC_SAR_SAMPLE_CTRL_REG &= (uint32)(~MyADC_CONTINUOUS_EN);
    #endif /* MyADC_DEFAULT_SAMPLE_MODE == MyADC__FREERUNNING */
}


/*******************************************************************************
* Function Name: MyADC_IsEndConversion
********************************************************************************
*
* Summary:
*  Description: Checks for ADC end of conversion for the case one
*  channel and end of scan for the case of multiple channels. It acts
*  as a software version of the EOC. This function provides the
*  programmer with two options. In one mode this function
*  immediately returns with the conversion status. In the other mode,
*  the function does not return (blocking) until the conversion has
*  completed.
*
* Parameters:
*  ADC_RETURN_STATUS        -> Immediately returns conversion result status
*  ADC_WAIT_FOR_RESULT      -> Does not return until ADC complete
*  ADC_RETURN_STATUS_INJ    -> Immediately returns conversion result status
*                              for injection channel
*  ADC_WAIT_FOR_RESULT_INJ  -> Does not return until ADC completes injection
*                              channel conversion
*
* Return:
*  If a non-zero value is returned, the last conversion or scan has completed.
*  If the returned value is zero, the ADC is still in the process of a scan.
*
*******************************************************************************/
uint32 MyADC_IsEndConversion(uint32 retMode)
{
    uint32 status = 0u;

    if((retMode & (MyADC_RETURN_STATUS | MyADC_WAIT_FOR_RESULT)) != 0u)
    {
        do
        {
            status = MyADC_SAR_INTR_REG & MyADC_EOS_MASK;
        }while((status == 0u) && ((retMode & MyADC_WAIT_FOR_RESULT) != 0u));

        if(status != 0u)
        {
            /* Clear EOS bit */
            MyADC_SAR_INTR_REG = MyADC_EOS_MASK;
        }
    }

    #if(MyADC_INJ_CHANNEL_ENABLED)
        if((retMode & (MyADC_RETURN_STATUS_INJ | MyADC_WAIT_FOR_RESULT_INJ)) != 0u)
        {
            do
            {
                status |= MyADC_SAR_INTR_REG & MyADC_INJ_EOC_MASK;
            }while(((status & MyADC_INJ_EOC_MASK) == 0u) &&
                   ((retMode & MyADC_WAIT_FOR_RESULT_INJ) != 0u));

            if((status & MyADC_INJ_EOC_MASK) != 0u)
            {
                /* Clear Injection EOS bit */
                MyADC_SAR_INTR_REG = MyADC_INJ_EOC_MASK;
            }
        }
    #endif /* MyADC_INJ_CHANNEL_ENABLED */

    return (status);
}


/*******************************************************************************
* Function Name: MyADC_GetResult16
********************************************************************************
*
* Summary:
*  Gets the data available in the SAR DATA register.
*
* Parameters:
*  chan: The ADC channel in which to return the result. The first channel
*  is 0 and the injection channel if enabled is the number of valid channels.
*
* Return:
*  Returns converted data as a signed 16-bit integer
*
*******************************************************************************/
int16 MyADC_GetResult16(uint32 chan)
{
    uint32 result;

    /* Halt CPU in debug mode if channel is out of valid range */
    CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

    if(chan < MyADC_SEQUENCED_CHANNELS_NUM)
    {
        result = CY_GET_REG32((reg32 *)(MyADC_SAR_CHAN_RESULT_IND + (uint32)(chan << 2u))) &
                MyADC_RESULT_MASK;
    }
    else
    {
        #if(MyADC_INJ_CHANNEL_ENABLED)
            result = MyADC_SAR_INJ_RESULT_REG & MyADC_RESULT_MASK;
        #else
            result = 0u;
        #endif /* MyADC_INJ_CHANNEL_ENABLED */
    }

    return ( (int16)result );
}


/*******************************************************************************
* Function Name: MyADC_SetChanMask
********************************************************************************
*
* Summary:
*  Sets the channel enable mask.
*
* Parameters:
*  mask: Sets which channels that will be
*  scanned. Setting bits for channels that do not exist will have no
*  effect. For example, if only 6 channels were enabled, setting a
*  mask of 0x0103 would only enable the last two channels (0 and 1).
*  This API will not enable the injection channel.
*  Examples: If the component is setup to sequence through 8
*  channels, a mask of 0x000F would enable channels 0, 1, 2, and 3.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SetChanMask(uint32 mask)
{
    MyADC_SAR_CHAN_EN_REG = mask & MyADC_MAX_CHANNELS_EN_MASK;
}

#if(MyADC_INJ_CHANNEL_ENABLED)


    /*******************************************************************************
    * Function Name: MyADC_EnableInjection
    ********************************************************************************
    *
    * Summary:
    *  Enables the injection channel for the next scan only.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void MyADC_EnableInjection(void)
    {
        MyADC_SAR_INJ_CHAN_CONFIG_REG |= MyADC_INJ_CHAN_EN;
    }

#endif /* MyADC_INJ_CHANNEL_ENABLED */


/*******************************************************************************
* Function Name: MyADC_SetLowLimit
********************************************************************************
*
* Summary:
*  Sets the low limit parameter for a limit condition.
*
* Parameters:
*  lowLimit: The low limit for a limit condition.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SetLowLimit(uint32 lowLimit)
{
    MyADC_SAR_RANGE_THRES_REG &= (uint32)(~MyADC_RANGE_LOW_MASK);
    MyADC_SAR_RANGE_THRES_REG |= lowLimit & MyADC_RANGE_LOW_MASK;
}


/*******************************************************************************
* Function Name: MyADC_SetHighLimit
********************************************************************************
*
* Summary:
*  Sets the low limit parameter for a limit condition.
*
* Parameters:
*  highLimit: The high limit for a limit condition.
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SetHighLimit(uint32 highLimit)
{
    MyADC_SAR_RANGE_THRES_REG &= (uint32)(~MyADC_RANGE_HIGH_MASK);
    MyADC_SAR_RANGE_THRES_REG |= (uint32)(highLimit << MyADC_RANGE_HIGH_OFFSET);
}


/*******************************************************************************
* Function Name: MyADC_SetLimitMask
********************************************************************************
*
* Summary:
*  Sets the channel limit condition mask.
*
* Parameters:
*  mask: Sets which channels that may cause a
*  limit condition interrupt. Setting bits for channels that do not exist
*  will have no effect. For example, if only 6 channels were enabled,
*  setting a mask of 0x0103 would only enable the last two channels (0 and 1).
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SetLimitMask(uint32 mask)
{
    MyADC_SAR_RANGE_INTR_MASK_REG = mask & MyADC_MAX_CHANNELS_EN_MASK;
}


/*******************************************************************************
* Function Name: MyADC_SetSatMask
********************************************************************************
*
* Summary:
*  Sets the channel saturation event mask.
*
* Parameters:
*  mask: Sets which channels that may cause a
*  saturation event interrupt. Setting bits for channels that do not exist
*  will have no effect. For example, if only 8 channels were enabled,
*  setting a mask of 0x01C0 would only enable two channels (6 and 7).
*
* Return:
*  None.
*
*******************************************************************************/
void MyADC_SetSatMask(uint32 mask)
{
    MyADC_SAR_SATURATE_INTR_MASK_REG = mask & MyADC_MAX_CHANNELS_EN_MASK;
}


/*******************************************************************************
* Function Name: MyADC_SetOffset
********************************************************************************
*
* Summary:
*   Description: Sets the ADC offset which is used by the functions
*   ADC_CountsTo_uVolts, ADC_CountsTo_mVolts and ADC_CountsTo_Volts
*   to substract the offset from the given reading
*   before calculating the voltage conversion.
*
* Parameters:
*  chan: ADC channel number.
*  offset: This value is a measured value when the
*          inputs are shorted or connected to the same input voltage.
*
* Return:
*  None.
*
* Global variables:
*  MyADC_Offset:  Modified to set the user provided offset.
*
*******************************************************************************/
void MyADC_SetOffset(uint32 chan, int16 offset)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

    MyADC_offset[chan] = offset;
}


/*******************************************************************************
* Function Name: MyADC_SetGain
********************************************************************************
*
* Summary:
*  Description: Sets the ADC gain in counts per 10 volt for the voltage
*  conversion functions below. This value is set by default by the
*  reference and input range settings. It should only be used to further
*  calibrate the ADC with a known input or if an external reference is
*  used. Affects the ADC_CountsTo_uVolts, ADC_CountsTo_mVolts
*  and ADC_CountsTo_Volts functions by supplying the correct
*  conversion between ADC counts and voltage.
*
* Parameters:
*  chan: ADC channel number.
*  adcGain: ADC gain in counts per 10 volts.
*
* Return:
*  None.
*
* Global variables:
*  MyADC_CountsPer10Volt:  modified to set the ADC gain in counts
*   per 10 volt.
*
*******************************************************************************/
void MyADC_SetGain(uint32 chan, int32 adcGain)
{
    /* Halt CPU in debug mode if channel is out of valid range */
    CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

    MyADC_countsPer10Volt[chan] = adcGain;
}


#if(MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT)


    /*******************************************************************************
    * Function Name: MyADC_CountsTo_mVolts
    ********************************************************************************
    *
    * Summary:
    *  This function converts ADC counts to mVolts
    *  This function is not available when left data format justification selected.
    *
    * Parameters:
    *  chan: The ADC channel number.
    *  adcCounts: Result from the ADC conversion
    *
    * Return:
    *  Results in mVolts
    *
    * Global variables:
    *  MyADC_countsPer10Volt:  used to convert ADC counts to mVolts.
    *  MyADC_Offset:  Used as the offset while converting ADC counts
    *   to mVolts.
    *
    *******************************************************************************/
    int16 MyADC_CountsTo_mVolts(uint32 chan, int16 adcCounts)
    {
        int16 mVolts;

        /* Halt CPU in debug mode if channel is out of valid range */
        CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

        /* Divide the adcCount when accumulate averaging mode selected */
        #if(MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE)
            if((MyADC_channelsConfig[chan] & MyADC_AVERAGING_EN) != 0u)
            {
                adcCounts /= MyADC_DEFAULT_AVG_SAMPLES_DIV;
            }
        #endif /* MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE */

        /* Subtract ADC offset */
        adcCounts -= MyADC_offset[chan];

        mVolts = (int16)((((int32)adcCounts * MyADC_10MV_COUNTS) + ( (adcCounts > 0) ?
                 (MyADC_countsPer10Volt[chan] / 2) : (-(MyADC_countsPer10Volt[chan] / 2)) ))
                 / MyADC_countsPer10Volt[chan]);

        return( mVolts );
    }


    /*******************************************************************************
    * Function Name: MyADC_CountsTo_uVolts
    ********************************************************************************
    *
    * Summary:
    *  This function converts ADC counts to micro Volts
    *  This function is not available when left data format justification selected.
    *
    * Parameters:
    *  chan: The ADC channel number.
    *  adcCounts: Result from the ADC conversion
    *
    * Return:
    *  Results in uVolts
    *
    * Global variables:
    *  MyADC_countsPer10Volt:  used to convert ADC counts to uVolts.
    *  MyADC_Offset:  Used as the offset while converting ADC counts
    *   to mVolts.
    *
    * Theory:
    *  Care must be taken to not exceed the maximum value for a 31 bit signed
    *  number in the conversion to uVolts and at the same time not loose
    *  resolution.
    *  To convert adcCounts to microVolts it is required to be multiplied
    *  on 10 million and later divide on gain in counts per 10V.
    *
    *******************************************************************************/
    int32 MyADC_CountsTo_uVolts(uint32 chan, int16 adcCounts)
    {
        int64 uVolts;

        /* Halt CPU in debug mode if channel is out of valid range */
        CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

        /* Divide the adcCount when accumulate averaging mode selected */
        #if(MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE)
            if((MyADC_channelsConfig[chan] & MyADC_AVERAGING_EN) != 0u)
            {
                adcCounts /= MyADC_DEFAULT_AVG_SAMPLES_DIV;
            }
        #endif /* MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE */

        /* Subtract ADC offset */
        adcCounts -= MyADC_offset[chan];

        uVolts = ((int64)adcCounts * MyADC_10UV_COUNTS) / MyADC_countsPer10Volt[chan];

        return( (int32)uVolts );
    }


    /*******************************************************************************
    * Function Name: MyADC_CountsTo_Volts
    ********************************************************************************
    *
    * Summary:
    *  Converts the ADC output to Volts as a floating point number.
    *  This function is not available when left data format justification selected.
    *
    * Parameters:
    *  chan: The ADC channel number.
    *  Result from the ADC conversion
    *
    * Return:
    *  Results in Volts
    *
    * Global variables:
    *  MyADC_countsPer10Volt:  used to convert ADC counts to Volts.
    *  MyADC_Offset:  Used as the offset while converting ADC counts
    *   to mVolts.
    *
    *******************************************************************************/
    float32 MyADC_CountsTo_Volts(uint32 chan, int16 adcCounts)
    {
        float32 volts;

        /* Halt CPU in debug mode if channel is out of valid range */
        CYASSERT(chan < MyADC_TOTAL_CHANNELS_NUM);

        /* Divide the adcCount when accumulate averaging mode selected */
        #if(MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE)
            if((MyADC_channelsConfig[chan] & MyADC_AVERAGING_EN) != 0u)
            {
                adcCounts /= MyADC_DEFAULT_AVG_SAMPLES_DIV;
            }
        #endif /* MyADC_DEFAULT_AVG_MODE == MyADC__ACCUMULATE */

        /* Subtract ADC offset */
        adcCounts -= MyADC_offset[chan];

        volts = ((float32)adcCounts * MyADC_10V_COUNTS) / (float32)MyADC_countsPer10Volt[chan];

        return( volts );
    }

#endif /* End MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT */


/* [] END OF FILE */
