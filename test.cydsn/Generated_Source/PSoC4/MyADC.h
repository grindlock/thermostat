/*******************************************************************************
* File Name: MyADC.h
* Version 2.50
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_MyADC_H)
#define CY_ADC_SAR_SEQ_MyADC_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint32 dftRegVal;
} MyADC_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
#define MyADC__EXTERNAL 0
#define MyADC__INTERNAL 1

/*  Sample Mode setting constants */
#define MyADC__FREERUNNING 0
#define MyADC__HARDWARESOC 1

/*  Reference type setting constants */
#define MyADC__VDDA_2 0
#define MyADC__VDDA 1
#define MyADC__INTERNAL1024 2
#define MyADC__INTERNAL1024BYPASSED 3
#define MyADC__INTERNALVREF 4
#define MyADC__INTERNALVREFBYPASSED 5
#define MyADC__VDDA_2BYPASSED 6
#define MyADC__EXTERNALVREF 7

/* Input buffer gain setting constants */
#define MyADC__DISABLED 0
#define MyADC__ONE 1
#define MyADC__TWO 2
#define MyADC__FOUR 3
#define MyADC__EIGHT 4
#define MyADC__SIXTEEN 5

/* Negative input setting sonstants in single ended mode */
#define MyADC__VSS 0
#define MyADC__VREF 1
#define MyADC__OTHER 2

/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define MyADC__MODE0 0
#define MyADC__MODE1 1
#define MyADC__MODE2 2
#define MyADC__MODE3 3

#define MyADC__RES8 0
#define MyADC__RES10 1

#define MyADC__RIGHT 0
#define MyADC__LEFT 1

#define MyADC__FSIGNED 1
#define MyADC__FUNSIGNED 0

#define MyADC__ACCUMULATE 0
#define MyADC__FIXEDRESOLUTION 1



/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#define MyADC_CY_SAR_IP_VER0               	(0u)
#define MyADC_CY_SAR_IP_VER1               	(1u)

#if (CY_PSOC4_4100 || CY_PSOC4_4200)
    #define MyADC_CY_SAR_IP_VER              (MyADC_CY_SAR_IP_VER0)
#else /* Other devices */
    #define MyADC_CY_SAR_IP_VER              (MyADC_CY_SAR_IP_VER1)
#endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */


/***************************************
*    Initial Parameter Constants
***************************************/
#define MyADC_DEFAULT_SAMPLE_MODE_SEL        (0u)
#define MyADC_DEFAULT_VREF_SEL               (2u)
#define MyADC_DEFAULT_NEG_INPUT_SEL          (0u)
#define MyADC_DEFAULT_ALT_RESOLUTION_SEL     (0u)
#define MyADC_DEFAULT_JUSTIFICATION_SEL      (0u)
#define MyADC_DEFAULT_DIFF_RESULT_FORMAT_SEL (0u)
#define MyADC_DEFAULT_SE_RESULT_FORMAT_SEL   (1u)
#define MyADC_DEFAULT_CLOCK_SOURCE           (1u)
#define MyADC_DEFAULT_VREF_MV_VALUE          (1024)
#define MyADC_DEFAULT_BUFFER_GAIN            (0u)
#define MyADC_DEFAULT_AVG_SAMPLES_NUM        (7u)
#define MyADC_DEFAULT_AVG_SAMPLES_DIV        (7u < 4u) ? (int16)(0x100u >> (7u - 7u)) : (int16)(0x100u >> 4u)
#define MyADC_DEFAULT_AVG_MODE               (1u)
#define MyADC_MAX_RESOLUTION                 (12u)
#define MyADC_DEFAULT_LOW_LIMIT              (0u)
#define MyADC_DEFAULT_HIGH_LIMIT             (2047u)
#define MyADC_DEFAULT_COMPARE_MODE           (0u)
#define MyADC_DEFAULT_ACLKS_NUM              (1023u)
#define MyADC_DEFAULT_BCLKS_NUM              (2u)
#define MyADC_DEFAULT_CCLKS_NUM              (2u)
#define MyADC_DEFAULT_DCLKS_NUM              (2u)
#define MyADC_TOTAL_CHANNELS_NUM             (1u)
#define MyADC_SEQUENCED_CHANNELS_NUM         (1u)
#define MyADC_DEFAULT_EN_CHANNELS            (1u)
#define MyADC_NOMINAL_CLOCK_FREQ             (1000000)
#define MyADC_INJ_CHANNEL_ENABLED            (0u)
#define MyADC_IRQ_REMOVE                     (0u)

/* Determines whether the configuration contains external negative input. */
#define MyADC_SINGLE_PRESENT                 (0u)
#define MyADC_CHANNELS_MODE                  (0u)
#define MyADC_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - MyADC_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void MyADC_Start(void);
void MyADC_Stop(void);
void MyADC_Init(void);
void MyADC_Enable(void);
void MyADC_StartConvert(void);
void MyADC_StopConvert(void);
uint32 MyADC_IsEndConversion(uint32 retMode);
int16 MyADC_GetResult16(uint32 chan);
void MyADC_SetChanMask(uint32 mask);
void MyADC_SetLowLimit(uint32 lowLimit);
void MyADC_SetHighLimit(uint32 highLimit);
void MyADC_SetLimitMask(uint32 mask);
void MyADC_SetSatMask(uint32 mask);
void MyADC_SetOffset(uint32 chan, int16 offset);
void MyADC_SetGain(uint32 chan, int32 adcGain);
#if(MyADC_INJ_CHANNEL_ENABLED)
    void MyADC_EnableInjection(void);
#endif /* MyADC_INJ_CHANNEL_ENABLED */
#if(MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT)
    int16 MyADC_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 MyADC_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 MyADC_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT */
void MyADC_Sleep(void);
void MyADC_Wakeup(void);
void MyADC_SaveConfig(void);
void MyADC_RestoreConfig(void);

CY_ISR_PROTO( MyADC_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define MyADC_DISABLED                   (0x00u)
#define MyADC_ENABLED                    (0x01u)
#define MyADC_STARTED                    (0x02u)
#define MyADC_BOOSTPUMP_ENABLED          (0x04u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define MyADC_RETURN_STATUS              (0x01u)
#define MyADC_WAIT_FOR_RESULT            (0x02u)
#define MyADC_RETURN_STATUS_INJ          (0x04u)
#define MyADC_WAIT_FOR_RESULT_INJ        (0x08u)

#define MyADC_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define MyADC_RESOLUTION_12              (12u)
#define MyADC_RESOLUTION_10              (10u)
#define MyADC_RESOLUTION_8               (8u)

#define MyADC_10US_DELAY                 (10u)

#define MyADC_10V_COUNTS                 (10.0F)
#define MyADC_10MV_COUNTS                (10000)
#define MyADC_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 MyADC_initVar;
extern volatile int16 MyADC_offset[MyADC_TOTAL_CHANNELS_NUM];
extern volatile int32 MyADC_countsPer10Volt[MyADC_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define MyADC_SAR_CTRL_REG                (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CTRL )
#define MyADC_SAR_CTRL_PTR                ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CTRL )

#define MyADC_SAR_SAMPLE_CTRL_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define MyADC_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define MyADC_SAR_SAMPLE_TIME01_REG       (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define MyADC_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define MyADC_SAR_SAMPLE_TIME23_REG       (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define MyADC_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define MyADC_SAR_RANGE_THRES_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_THRES )
#define MyADC_SAR_RANGE_THRES_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_THRES )

#define MyADC_SAR_RANGE_COND_REG          (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_COND )
#define MyADC_SAR_RANGE_COND_PTR          ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_COND )

#define MyADC_SAR_CHAN_EN_REG             (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_EN )
#define MyADC_SAR_CHAN_EN_PTR             ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_EN )

#define MyADC_SAR_START_CTRL_REG          (*(reg32 *) MyADC_cy_psoc4_sar__SAR_START_CTRL )
#define MyADC_SAR_START_CTRL_PTR          ( (reg32 *) MyADC_cy_psoc4_sar__SAR_START_CTRL )

#define MyADC_SAR_DFT_CTRL_REG            (*(reg32 *) MyADC_cy_psoc4_sar__SAR_DFT_CTRL )
#define MyADC_SAR_DFT_CTRL_PTR            ( (reg32 *) MyADC_cy_psoc4_sar__SAR_DFT_CTRL )

#define MyADC_SAR_CHAN_CONFIG_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define MyADC_SAR_CHAN_CONFIG_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_CONFIG00 )
#define MyADC_SAR_CHAN_CONFIG_IND         MyADC_cy_psoc4_sar__SAR_CHAN_CONFIG00

#define MyADC_SAR_CHAN_WORK_REG           (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_WORK00 )
#define MyADC_SAR_CHAN_WORK_PTR           ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_WORK00 )

#define MyADC_SAR_CHAN_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define MyADC_SAR_CHAN_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define MyADC_SAR_CHAN_RESULT_IND         MyADC_cy_psoc4_sar__SAR_CHAN_RESULT00

#define MyADC_SAR_CHAN0_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT00 )
#define MyADC_SAR_CHAN0_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT00 )

#define MyADC_SAR_CHAN1_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT01 )
#define MyADC_SAR_CHAN1_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT01 )

#define MyADC_SAR_CHAN2_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT02 )
#define MyADC_SAR_CHAN2_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT02 )

#define MyADC_SAR_CHAN3_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT03 )
#define MyADC_SAR_CHAN3_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT03 )

#define MyADC_SAR_CHAN4_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT04 )
#define MyADC_SAR_CHAN4_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT04 )

#define MyADC_SAR_CHAN5_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT05 )
#define MyADC_SAR_CHAN5_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT05 )

#define MyADC_SAR_CHAN6_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT06 )
#define MyADC_SAR_CHAN6_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT06 )

#define MyADC_SAR_CHAN7_RESULT_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT07 )
#define MyADC_SAR_CHAN7_RESULT_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT07 )

#if(MyADC_CY_SAR_IP_VER != MyADC_CY_SAR_IP_VER0)
    #define MyADC_SAR_CHAN8_RESULT_REG     (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT08 )
    #define MyADC_SAR_CHAN8_RESULT_PTR     ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT08 )

    #define MyADC_SAR_CHAN9_RESULT_REG     (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT09 )
    #define MyADC_SAR_CHAN9_RESULT_PTR     ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT09 )

    #define MyADC_SAR_CHAN10_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT10 )
    #define MyADC_SAR_CHAN10_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT10 )

    #define MyADC_SAR_CHAN11_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT11 )
    #define MyADC_SAR_CHAN11_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT11 )

    #define MyADC_SAR_CHAN12_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT12 )
    #define MyADC_SAR_CHAN12_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT12 )

    #define MyADC_SAR_CHAN13_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT13 )
    #define MyADC_SAR_CHAN13_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT13 )

    #define MyADC_SAR_CHAN14_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT14 )
    #define MyADC_SAR_CHAN14_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT14 )

    #define MyADC_SAR_CHAN15_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT15 )
    #define MyADC_SAR_CHAN15_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT15 )
#endif /* (MyADC_CY_SAR_IP_VER != MyADC_CY_SAR_IP_VER0) */

#define MyADC_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_WORK_VALID)
#define MyADC_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_WORK_VALID)

#define MyADC_SAR_CHAN_RESULT_VALID_REG  ( *(reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )
#define MyADC_SAR_CHAN_RESULT_VALID_PTR  ( (reg32 *) MyADC_cy_psoc4_sar__SAR_CHAN_RESULT_VALID )

#define MyADC_SAR_STATUS_REG              (*(reg32 *) MyADC_cy_psoc4_sar__SAR_STATUS )
#define MyADC_SAR_STATUS_PTR              ( (reg32 *) MyADC_cy_psoc4_sar__SAR_STATUS )

#define MyADC_SAR_AVG_START_REG           (*(reg32 *) MyADC_cy_psoc4_sar__SAR_AVG_STAT )
#define MyADC_SAR_AVG_START_PTR           ( (reg32 *) MyADC_cy_psoc4_sar__SAR_AVG_STAT )

#define MyADC_SAR_INTR_REG                (*(reg32 *) MyADC_cy_psoc4_sar__SAR_INTR )
#define MyADC_SAR_INTR_PTR                ( (reg32 *) MyADC_cy_psoc4_sar__SAR_INTR )

#define MyADC_SAR_INTR_SET_REG            (*(reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_SET )
#define MyADC_SAR_INTR_SET_PTR            ( (reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_SET )

#define MyADC_SAR_INTR_MASK_REG           (*(reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_MASK )
#define MyADC_SAR_INTR_MASK_PTR           ( (reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_MASK )

#define MyADC_SAR_INTR_MASKED_REG         (*(reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_MASKED )
#define MyADC_SAR_INTR_MASKED_PTR         ( (reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_MASKED )

#define MyADC_SAR_SATURATE_INTR_REG       (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR )
#define MyADC_SAR_SATURATE_INTR_PTR       ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR )

#define MyADC_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define MyADC_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define MyADC_SAR_SATURATE_INTR_MASK_REG (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define MyADC_SAR_SATURATE_INTR_MASK_PTR ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define MyADC_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define MyADC_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) MyADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define MyADC_SAR_RANGE_INTR_REG          (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR )
#define MyADC_SAR_RANGE_INTR_PTR          ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR )

#define MyADC_SAR_RANGE_INTR_SET_REG      (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define MyADC_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define MyADC_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define MyADC_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define MyADC_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define MyADC_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) MyADC_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define MyADC_SAR_INTR_CAUSE_REG          (*(reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_CAUSE )
#define MyADC_SAR_INTR_CAUSE_PTR          ( (reg32 *) MyADC_cy_psoc4_sar__SAR_INTR_CAUSE )

#if(MyADC_INJ_CHANNEL_ENABLED)
    #define MyADC_SAR_INJ_CHAN_CONFIG_REG \
                                                 (*(reg32 *) MyADC_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )
    #define MyADC_SAR_INJ_CHAN_CONFIG_PTR    \
                                                 ( (reg32 *) MyADC_cy_psoc4_sarmux_8__SAR_INJ_CHAN_CONFIG )

    #define MyADC_SAR_INJ_RESULT_REG    (*(reg32 *) MyADC_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
    #define MyADC_SAR_INJ_RESULT_PTR    ( (reg32 *) MyADC_cy_psoc4_sarmux_8__SAR_INJ_RESULT )
#endif /* MyADC_INJ_CHANNEL_ENABLED */
    
#define MyADC_MUX_SWITCH0_REG           (*(reg32 *)  MyADC_cy_psoc4_sar__SAR_MUX_SWITCH0 )
#define MyADC_MUX_SWITCH0_PTR           ( (reg32 *)  MyADC_cy_psoc4_sar__SAR_MUX_SWITCH0 )

#define MyADC_MUX_SWITCH_HW_CTRL_REG    (*(reg32 *)  MyADC_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )
#define MyADC_MUX_SWITCH_HW_CTRL_PTR    ( (reg32 *)  MyADC_cy_psoc4_sar__SAR_MUX_SWITCH_HW_CTRL )

#define MyADC_PUMP_CTRL_REG             (*(reg32 *)  MyADC_cy_psoc4_sar__SAR_PUMP_CTRL )
#define MyADC_PUMP_CTRL_PTR             ( (reg32 *)  MyADC_cy_psoc4_sar__SAR_PUMP_CTRL )

#define MyADC_ANA_TRIM_REG              (*(reg32 *)  MyADC_cy_psoc4_sar__SAR_ANA_TRIM )
#define MyADC_ANA_TRIM_PTR              ( (reg32 *)  MyADC_cy_psoc4_sar__SAR_ANA_TRIM )

#define MyADC_WOUNDING_REG              (*(reg32 *)  MyADC_cy_psoc4_sar__SAR_WOUNDING )
#define MyADC_WOUNDING_PTR              ( (reg32 *)  MyADC_cy_psoc4_sar__SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define MyADC_INTC_NUMBER                (MyADC_IRQ__INTC_NUMBER)
#define MyADC_INTC_PRIOR_NUMBER          (MyADC_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define MyADC_VREF_INTERNAL1024          (0x00000040Lu)
#define MyADC_VREF_EXTERNAL              (0x00000050Lu)
#define MyADC_VREF_VDDA_2                (0x00000060Lu)
#define MyADC_VREF_VDDA                  (0x00000070Lu)
#define MyADC_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define MyADC_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define MyADC_VREF_INTERNALVREF          (0x00000040Lu)
#define MyADC_VREF_INTERNALVREFBYPASSED  (0x000000C0Lu)

#define MyADC_NEG_VSSA_KELVIN            (0x00000000Lu)
#define MyADC_NEG_VSSA                   (0x00000200Lu)
#define MyADC_NEG_VREF                   (0x00000E00Lu)
#if(MyADC_TOTAL_CHANNELS_NUM > 1u)
    #define MyADC_NEG_OTHER              (uint16)((uint16)MyADC_cy_psoc4_sarmux_8__VNEG0 << 9u)
#else
    #define MyADC_NEG_OTHER              (0)
#endif /* MyADC_TOTAL_CHANNELS_NUM > 1u */

#define MyADC_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define MyADC_BOOSTPUMP_EN               (0x00100000Lu)

#define MyADC_NORMAL_PWR                 (0x00000000Lu)
#define MyADC_HALF_PWR                   (0x01000000Lu)
#define MyADC_MORE_PWR                   (0x02000000Lu)
#define MyADC_QUARTER_PWR                (0x03000000Lu)
#define MyADC_DEEPSLEEP_ON               (0x08000000Lu)

#define MyADC_DSI_SYNC_CONFIG            (0x10000000Lu)
#define MyADC_DSI_MODE                   (0x20000000Lu)
#define MyADC_SWITCH_DISABLE             (0x40000000Lu)
#define MyADC_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define MyADC_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define MyADC_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define MyADC_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define MyADC_DATA_ALIGN_LEFT            (0x00000002Lu)
#define MyADC_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define MyADC_SE_SIGNED_RESULT           (0x00000004Lu)
#define MyADC_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define MyADC_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define MyADC_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define MyADC_AVG_CNT_OFFSET             (4u)
#define MyADC_AVG_CNT_MASK               (0x00000070Lu)
#define MyADC_AVG_SHIFT                  (0x00000080Lu)

#define MyADC_CONTINUOUS_EN              (0x00010000Lu)
#define MyADC_DSI_TRIGGER_EN             (0x00020000Lu)
#define MyADC_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define MyADC_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define MyADC_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define MyADC_SAMPLE_TIME13_OFFSET       (16u)
#define MyADC_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define MyADC_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define MyADC_RANGE_HIGH_OFFSET          (16u)
#define MyADC_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define MyADC_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define MyADC_CMP_MODE_BELOW             (0x00000000Lu)
#define MyADC_CMP_MODE_INSIDE            (0x40000000Lu)
#define MyADC_CMP_MODE_ABOVE             (0x80000000Lu)
#define MyADC_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define MyADC_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define MyADC_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define MyADC_DLY_INC                    (0x00000001Lu)
#define MyADC_HIZ                        (0x00000002Lu)
#define MyADC_DFT_INC_MASK               (0x000F0000Lu)
#define MyADC_DFT_OUTC_MASK              (0x00700000Lu)
#define MyADC_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define MyADC_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define MyADC_EN_CSEL_DFT                (0x10000000Lu)
#define MyADC_DCEN                       (0x20000000Lu)
#define MyADC_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define MyADC_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define MyADC_DIFFERENTIAL_EN            (0x00000100Lu)
#define MyADC_ALT_RESOLUTION_ON          (0x00000200Lu)
#define MyADC_AVERAGING_EN               (0x00000400Lu)

#define MyADC_SAMPLE_TIME_SEL_SHIFT      (12u)
#define MyADC_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define MyADC_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define MyADC_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define MyADC_INJ_TAILGATING             (0x40000000Lu)
#define MyADC_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define MyADC_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define MyADC_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define MyADC_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define MyADC_RESULT_MASK                (0x0000FFFFLu)
#define MyADC_SATURATE_INTR_MIR          (0x20000000Lu)
#define MyADC_RANGE_INTR_MIR             (0x40000000Lu)
#define MyADC_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define MyADC_EOS_MASK                   (0x00000001Lu)
#define MyADC_OVERFLOW_MASK              (0x00000002Lu)
#define MyADC_FW_COLLISION_MASK          (0x00000004Lu)
#define MyADC_DSI_COLLISION_MASK         (0x00000008Lu)
#define MyADC_INJ_EOC_MASK               (0x00000010Lu)
#define MyADC_INJ_SATURATE_MASK          (0x00000020Lu)
#define MyADC_INJ_RANGE_MASK             (0x00000040Lu)
#define MyADC_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define MyADC_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define MyADC_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define MyADC_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define MyADC_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define MyADC_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define MyADC_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define MyADC_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define MyADC_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define MyADC_WOUNDING_12BIT             (0x00000000Lu)
#define MyADC_WOUNDING_10BIT             (0x00000001Lu)
#define MyADC_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define MyADC_TRIM_COEF                  (2u)

#if(MyADC_MAX_RESOLUTION == MyADC_RESOLUTION_10)
    #define MyADC_ALT_WOUNDING           MyADC_WOUNDING_10BIT
#else
    #define MyADC_ALT_WOUNDING           MyADC_WOUNDING_8BIT
#endif /* MyADC_MAX_RESOLUTION == MyADC_RESOLUTION_10 */

#if(MyADC_DEFAULT_VREF_SEL == MyADC__VDDA_2)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_VDDA_2
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__VDDA)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_VDDA
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__INTERNAL1024)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_INTERNAL1024
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__INTERNAL1024BYPASSED)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_INTERNAL1024BYPASSED
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__INTERNALVREF)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_INTERNALVREF
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__INTERNALVREFBYPASSED)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_INTERNALVREFBYPASSED
#elif(MyADC_DEFAULT_VREF_SEL == MyADC__VDDA_2BYPASSED)
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_VDDA_2BYPASSED
#else
    #define MyADC_DEFAULT_VREF_SOURCE    MyADC_VREF_EXTERNAL
#endif /* MyADC_DEFAULT_VREF_SEL == MyADC__VDDA_2 */

#if(MyADC_DEFAULT_NEG_INPUT_SEL == MyADC__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(MyADC_TOTAL_CHANNELS_NUM == 1u)
        #define MyADC_DEFAULT_SE_NEG_INPUT    MyADC_NEG_VSSA
    #else
        #define MyADC_DEFAULT_SE_NEG_INPUT    MyADC_NEG_VSSA_KELVIN
    #endif /* (MyADC_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((MyADC_TOTAL_CHANNELS_NUM == 1u) && (MyADC_CHANNELS_MODE != 0u))
        #define MyADC_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define MyADC_DEFAULT_MUX_SWITCH0     MyADC_MUX_FW_VSSA_VMINUS
    #endif /* (MyADC_TOTAL_CHANNELS_NUM == 1u) */
#elif(MyADC_DEFAULT_NEG_INPUT_SEL == MyADC__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((MyADC_TOTAL_CHANNELS_NUM == 1u) && (MyADC_CHANNELS_MODE != 0u))
        #define MyADC_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define MyADC_DEFAULT_SE_NEG_INPUT    MyADC_NEG_VREF
    #endif /* (MyADC_TOTAL_CHANNELS_NUM == 1u) */
    #define MyADC_DEFAULT_MUX_SWITCH0     0u
#elif (MyADC_SINGLE_PRESENT != 0u)
    #define MyADC_DEFAULT_SE_NEG_INPUT    MyADC_NEG_OTHER
    #define MyADC_DEFAULT_MUX_SWITCH0     0u
#else
    #define MyADC_DEFAULT_SE_NEG_INPUT    0u
    #define MyADC_DEFAULT_MUX_SWITCH0     0u
#endif /* MyADC_DEFAULT_NEG_INPUT_SEL == MyADC__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(MyADC_TOTAL_CHANNELS_NUM == 1u)
    #define MyADC_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define MyADC_DEFAULT_HW_CTRL_NEGVREF MyADC_SAR_HW_CTRL_NEGVREF
#endif /* (MyADC_TOTAL_CHANNELS_NUM == 1u) */


#if(MyADC_DEFAULT_ALT_RESOLUTION_SEL == MyADC__RES8)
    #define MyADC_DEFAULT_ALT_RESOLUTION     (MyADC_ALT_RESOLUTION_8BIT)
    #define MyADC_DEFAULT_MAX_WRK_ALT        (MyADC_SAR_WRK_MAX_8BIT)
#else
    #define MyADC_DEFAULT_ALT_RESOLUTION     (MyADC_ALT_RESOLUTION_10BIT)
    #define MyADC_DEFAULT_MAX_WRK_ALT        (MyADC_SAR_WRK_MAX_10BIT)
#endif /* End MyADC_DEFAULT_ALT_RESOLUTION_SEL == MyADC__RES8 */

#if(MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT)
    #define MyADC_DEFAULT_JUSTIFICATION  MyADC_DATA_ALIGN_RIGHT
#else
    #define MyADC_DEFAULT_JUSTIFICATION  MyADC_DATA_ALIGN_LEFT
#endif /* MyADC_DEFAULT_JUSTIFICATION_SEL == MyADC__RIGHT */

#if(MyADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MyADC__FSIGNED)
    #define MyADC_DEFAULT_DIFF_RESULT_FORMAT MyADC_DIFF_SIGNED_RESULT
#else
    #define MyADC_DEFAULT_DIFF_RESULT_FORMAT MyADC_DIFF_UNSIGNED_RESULT
#endif /* MyADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MyADC__FSIGNED */

#if(MyADC_DEFAULT_SE_RESULT_FORMAT_SEL == MyADC__FSIGNED)
    #define MyADC_DEFAULT_SE_RESULT_FORMAT MyADC_SE_SIGNED_RESULT
#else
    #define MyADC_DEFAULT_SE_RESULT_FORMAT MyADC_SE_UNSIGNED_RESULT
#endif /* MyADC_DEFAULT_SE_RESULT_FORMAT_SEL == MyADC__FSIGNED */

#if(MyADC_DEFAULT_SAMPLE_MODE_SEL == MyADC__FREERUNNING)
    #define MyADC_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define MyADC_DSI_TRIGGER        (MyADC_DSI_TRIGGER_EN | MyADC_DSI_SYNC_TRIGGER)
#endif /* End MyADC_DEFAULT_SAMPLE_MODE == MyADC__FREERUNNING */

#if(MyADC_INJ_CHANNEL_ENABLED)
    #define MyADC_SAR_INTR_MASK      (MyADC_EOS_MASK | MyADC_INJ_EOC_MASK)
#else
    #define MyADC_SAR_INTR_MASK      (MyADC_EOS_MASK)
#endif /* MyADC_INJ_CHANNEL_ENABLED*/

#if(MyADC_DEFAULT_AVG_MODE == MyADC__FIXEDRESOLUTION)
    #define MyADC_AVG_SHIFT_MODE     MyADC_AVG_SHIFT
#else
    #define MyADC_AVG_SHIFT_MODE     0u
#endif /* End MyADC_DEFAULT_AVG_MODE */

#define MyADC_COMPARE_MODE           (uint32)((uint32)(MyADC_DEFAULT_COMPARE_MODE) \
                                                << MyADC_CMP_OFFSET)

#if(MyADC_TOTAL_CHANNELS_NUM > 1u)
    #define MyADC_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define MyADC_DEFAULT_SWITCH_CONF    MyADC_SWITCH_DISABLE
#endif /* End MyADC_TOTAL_CHANNELS_NUM > 1 */

#define MyADC_DEFAULT_POWER \
       ((MyADC_NOMINAL_CLOCK_FREQ > (MyADC_MAX_FREQUENCY / 4)) ? MyADC_NORMAL_PWR : \
       ((MyADC_NOMINAL_CLOCK_FREQ > (MyADC_MAX_FREQUENCY / 8)) ? MyADC_HALF_PWR : \
                                                                                       MyADC_QUARTER_PWR))

#define MyADC_DEFAULT_CTRL_REG_CFG       (MyADC_DEFAULT_VREF_SOURCE \
                                                   | MyADC_DEFAULT_SE_NEG_INPUT \
                                                   | MyADC_DEFAULT_HW_CTRL_NEGVREF \
                                                   | MyADC_DEFAULT_POWER \
                                                   | MyADC_DSI_SYNC_CONFIG \
                                                   | MyADC_DEFAULT_SWITCH_CONF)

#define MyADC_DEFAULT_SAMPLE_CTRL_REG_CFG (MyADC_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | MyADC_DEFAULT_SE_RESULT_FORMAT \
                                                    | MyADC_DEFAULT_JUSTIFICATION \
                                                    | MyADC_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(MyADC_DEFAULT_AVG_SAMPLES_NUM \
                                                   << MyADC_AVG_CNT_OFFSET) \
                                                    | MyADC_AVG_SHIFT_MODE \
                                                    | MyADC_DSI_TRIGGER \
                                                    | MyADC_EOS_DSI_OUT_EN)

#define MyADC_DEFAULT_RANGE_THRES_REG_CFG (MyADC_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)MyADC_DEFAULT_HIGH_LIMIT << MyADC_RANGE_HIGH_OFFSET))

#define MyADC_DEFAULT_SAMPLE_TIME01_REG_CFG (MyADC_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)MyADC_DEFAULT_BCLKS_NUM << MyADC_SAMPLE_TIME13_OFFSET))

#define MyADC_DEFAULT_SAMPLE_TIME23_REG_CFG (MyADC_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)MyADC_DEFAULT_DCLKS_NUM << MyADC_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_MyADC_H */


/* [] END OF FILE */
