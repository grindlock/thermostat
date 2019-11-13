/***************************************************************************//**
* \file I2C_1_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_PVT.h"
#include "I2C_1_SPI_UART_PVT.h"

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const I2C_1_SPI_INIT_STRUCT I2C_1_configSpi =
    {
        I2C_1_SPI_MODE,
        I2C_1_SPI_SUB_MODE,
        I2C_1_SPI_CLOCK_MODE,
        I2C_1_SPI_OVS_FACTOR,
        I2C_1_SPI_MEDIAN_FILTER_ENABLE,
        I2C_1_SPI_LATE_MISO_SAMPLE_ENABLE,
        I2C_1_SPI_WAKE_ENABLE,
        I2C_1_SPI_RX_DATA_BITS_NUM,
        I2C_1_SPI_TX_DATA_BITS_NUM,
        I2C_1_SPI_BITS_ORDER,
        I2C_1_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) I2C_1_SCB_IRQ_INTERNAL,
        I2C_1_SPI_INTR_RX_MASK,
        I2C_1_SPI_RX_TRIGGER_LEVEL,
        I2C_1_SPI_INTR_TX_MASK,
        I2C_1_SPI_TX_TRIGGER_LEVEL,
        (uint8) I2C_1_SPI_BYTE_MODE_ENABLE,
        (uint8) I2C_1_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) I2C_1_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: I2C_1_SpiInit
    ****************************************************************************//**
    *
    *  Configures the I2C_1 for SPI operation.
    *
    *  This function is intended specifically to be used when the I2C_1 
    *  configuration is set to “Unconfigured I2C_1” in the customizer. 
    *  After initializing the I2C_1 in SPI mode using this function, 
    *  the component can be enabled using the I2C_1_Start() or 
    * I2C_1_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void I2C_1_SpiInit(const I2C_1_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            I2C_1_SetPins(I2C_1_SCB_MODE_SPI, config->mode, I2C_1_DUMMY_PARAM);

            /* Store internal configuration */
            I2C_1_scbMode       = (uint8) I2C_1_SCB_MODE_SPI;
            I2C_1_scbEnableWake = (uint8) config->enableWake;
            I2C_1_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            I2C_1_rxBuffer      =         config->rxBuffer;
            I2C_1_rxDataBits    = (uint8) config->rxDataBits;
            I2C_1_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            I2C_1_txBuffer      =         config->txBuffer;
            I2C_1_txDataBits    = (uint8) config->txDataBits;
            I2C_1_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            I2C_1_CTRL_REG     = I2C_1_GET_CTRL_OVS(config->oversample)           |
                                            I2C_1_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            I2C_1_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            I2C_1_CTRL_SPI;

            I2C_1_SPI_CTRL_REG = I2C_1_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            I2C_1_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          I2C_1_SPI_MODE_TI_PRECEDES_MASK) |
                                            I2C_1_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            I2C_1_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            I2C_1_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            I2C_1_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            I2C_1_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            I2C_1_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            I2C_1_RX_CTRL_REG     =  I2C_1_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                I2C_1_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                I2C_1_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                I2C_1_SPI_RX_CTRL;

            I2C_1_RX_FIFO_CTRL_REG = I2C_1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            I2C_1_TX_CTRL_REG      = I2C_1_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                I2C_1_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                I2C_1_SPI_TX_CTRL;

            I2C_1_TX_FIFO_CTRL_REG = I2C_1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (I2C_1_ISR_NUMBER);
            CyIntSetPriority(I2C_1_ISR_NUMBER, I2C_1_ISR_PRIORITY);
            (void) CyIntSetVector(I2C_1_ISR_NUMBER, &I2C_1_SPI_UART_ISR);

            /* Configure interrupt sources */
            I2C_1_INTR_I2C_EC_MASK_REG = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_SPI_EC_MASK_REG = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_SLAVE_MASK_REG  = I2C_1_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            I2C_1_INTR_MASTER_MASK_REG = I2C_1_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            I2C_1_INTR_RX_MASK_REG     = I2C_1_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            I2C_1_INTR_TX_MASK_REG     = I2C_1_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            I2C_1_IntrTxMask = LO16(I2C_1_INTR_TX_MASK_REG);

            /* Set active SS0 */
            I2C_1_SpiSetActiveSlaveSelect(I2C_1_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            I2C_1_rxBufferHead     = 0u;
            I2C_1_rxBufferTail     = 0u;
            I2C_1_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            I2C_1_txBufferHead = 0u;
            I2C_1_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: I2C_1_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void I2C_1_SpiInit(void)
    {
        /* Configure SPI interface */
        I2C_1_CTRL_REG     = I2C_1_SPI_DEFAULT_CTRL;
        I2C_1_SPI_CTRL_REG = I2C_1_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        I2C_1_RX_CTRL_REG      = I2C_1_SPI_DEFAULT_RX_CTRL;
        I2C_1_RX_FIFO_CTRL_REG = I2C_1_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        I2C_1_TX_CTRL_REG      = I2C_1_SPI_DEFAULT_TX_CTRL;
        I2C_1_TX_FIFO_CTRL_REG = I2C_1_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(I2C_1_SCB_IRQ_INTERNAL)
            CyIntDisable    (I2C_1_ISR_NUMBER);
            CyIntSetPriority(I2C_1_ISR_NUMBER, I2C_1_ISR_PRIORITY);
            (void) CyIntSetVector(I2C_1_ISR_NUMBER, &I2C_1_SPI_UART_ISR);
    #endif /* (I2C_1_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        I2C_1_INTR_I2C_EC_MASK_REG = I2C_1_SPI_DEFAULT_INTR_I2C_EC_MASK;
        I2C_1_INTR_SPI_EC_MASK_REG = I2C_1_SPI_DEFAULT_INTR_SPI_EC_MASK;
        I2C_1_INTR_SLAVE_MASK_REG  = I2C_1_SPI_DEFAULT_INTR_SLAVE_MASK;
        I2C_1_INTR_MASTER_MASK_REG = I2C_1_SPI_DEFAULT_INTR_MASTER_MASK;
        I2C_1_INTR_RX_MASK_REG     = I2C_1_SPI_DEFAULT_INTR_RX_MASK;
        I2C_1_INTR_TX_MASK_REG     = I2C_1_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        I2C_1_IntrTxMask = LO16(I2C_1_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (I2C_1_SPI_MASTER_CONST)
        I2C_1_SpiSetActiveSlaveSelect(I2C_1_SPI_SLAVE_SELECT0);
    #endif /* (I2C_1_SPI_MASTER_CONST) */

    #if(I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
        I2C_1_rxBufferHead     = 0u;
        I2C_1_rxBufferTail     = 0u;
        I2C_1_rxBufferOverflow = 0u;
    #endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
        I2C_1_txBufferHead = 0u;
        I2C_1_txBufferTail = 0u;
    #endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: I2C_1_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void I2C_1_SpiPostEnable(void)
{
#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if (I2C_1_CHECK_SPI_MASTER)
    {
    #if (I2C_1_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_CTS_SCLK_HSIOM_REG, I2C_1_CTS_SCLK_HSIOM_MASK,
                                       I2C_1_CTS_SCLK_HSIOM_POS, I2C_1_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (I2C_1_CTS_SCLK_PIN) */

    #if (I2C_1_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_RTS_SS0_HSIOM_REG, I2C_1_RTS_SS0_HSIOM_MASK,
                                       I2C_1_RTS_SS0_HSIOM_POS, I2C_1_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (I2C_1_RTS_SS0_PIN) */

    #if (I2C_1_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS1_HSIOM_REG, I2C_1_SS1_HSIOM_MASK,
                                       I2C_1_SS1_HSIOM_POS, I2C_1_SS1_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SS1_PIN) */

    #if (I2C_1_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS2_HSIOM_REG, I2C_1_SS2_HSIOM_MASK,
                                       I2C_1_SS2_HSIOM_POS, I2C_1_SS2_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SS2_PIN) */

    #if (I2C_1_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS3_HSIOM_REG, I2C_1_SS3_HSIOM_MASK,
                                       I2C_1_SS3_HSIOM_POS, I2C_1_SS3_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SS3_PIN) */
    }

#else

    #if (I2C_1_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SCLK_M_HSIOM_REG, I2C_1_SCLK_M_HSIOM_MASK,
                                       I2C_1_SCLK_M_HSIOM_POS, I2C_1_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (I2C_1_MISO_SDA_TX_PIN_PIN) */

    #if (I2C_1_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS0_M_HSIOM_REG, I2C_1_SS0_M_HSIOM_MASK,
                                       I2C_1_SS0_M_HSIOM_POS, I2C_1_SS0_M_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SPI_MASTER_SS0_PIN) */

    #if (I2C_1_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS1_M_HSIOM_REG, I2C_1_SS1_M_HSIOM_MASK,
                                       I2C_1_SS1_M_HSIOM_POS, I2C_1_SS1_M_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SPI_MASTER_SS1_PIN) */

    #if (I2C_1_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS2_M_HSIOM_REG, I2C_1_SS2_M_HSIOM_MASK,
                                       I2C_1_SS2_M_HSIOM_POS, I2C_1_SS2_M_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SPI_MASTER_SS2_PIN) */

    #if (I2C_1_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS3_M_HSIOM_REG, I2C_1_SS3_M_HSIOM_MASK,
                                       I2C_1_SS3_M_HSIOM_POS, I2C_1_SS3_M_HSIOM_SEL_SPI);
    #endif /* (I2C_1_SPI_MASTER_SS3_PIN) */

#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    I2C_1_SetTxInterruptMode(I2C_1_IntrTxMask);
}


/*******************************************************************************
* Function Name: I2C_1_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void I2C_1_SpiStop(void)
{
#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    if (I2C_1_CHECK_SPI_MASTER)
    {
    #if (I2C_1_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_uart_cts_spi_sclk_Write(I2C_1_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_CTS_SCLK_HSIOM_REG, I2C_1_CTS_SCLK_HSIOM_MASK,
                                       I2C_1_CTS_SCLK_HSIOM_POS, I2C_1_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_uart_cts_spi_sclk_PIN) */

    #if (I2C_1_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_uart_rts_spi_ss0_Write(I2C_1_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_RTS_SS0_HSIOM_REG, I2C_1_RTS_SS0_HSIOM_MASK,
                                       I2C_1_RTS_SS0_HSIOM_POS, I2C_1_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_uart_rts_spi_ss0_PIN) */

    #if (I2C_1_SS1_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_spi_ss1_Write(I2C_1_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS1_HSIOM_REG, I2C_1_SS1_HSIOM_MASK,
                                       I2C_1_SS1_HSIOM_POS, I2C_1_SS1_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_SS1_PIN) */

    #if (I2C_1_SS2_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_spi_ss2_Write(I2C_1_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS2_HSIOM_REG, I2C_1_SS2_HSIOM_MASK,
                                       I2C_1_SS2_HSIOM_POS, I2C_1_SS2_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_SS2_PIN) */

    #if (I2C_1_SS3_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_spi_ss3_Write(I2C_1_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_SS3_HSIOM_REG, I2C_1_SS3_HSIOM_MASK,
                                       I2C_1_SS3_HSIOM_POS, I2C_1_SS3_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        I2C_1_IntrTxMask = LO16(I2C_1_GetTxInterruptMode() & I2C_1_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        I2C_1_IntrTxMask = LO16(I2C_1_GetTxInterruptMode() & I2C_1_INTR_SPIS_TX_RESTORE);
    }

#else

#if (I2C_1_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    I2C_1_sclk_m_Write(I2C_1_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    I2C_1_SET_HSIOM_SEL(I2C_1_SCLK_M_HSIOM_REG, I2C_1_SCLK_M_HSIOM_MASK,
                                   I2C_1_SCLK_M_HSIOM_POS, I2C_1_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (I2C_1_MISO_SDA_TX_PIN_PIN) */

#if (I2C_1_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    I2C_1_ss0_m_Write(I2C_1_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    I2C_1_SET_HSIOM_SEL(I2C_1_SS0_M_HSIOM_REG, I2C_1_SS0_M_HSIOM_MASK,
                                   I2C_1_SS0_M_HSIOM_POS, I2C_1_SS0_M_HSIOM_SEL_GPIO);
#endif /* (I2C_1_SPI_MASTER_SS0_PIN) */

#if (I2C_1_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    I2C_1_ss1_m_Write(I2C_1_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    I2C_1_SET_HSIOM_SEL(I2C_1_SS1_M_HSIOM_REG, I2C_1_SS1_M_HSIOM_MASK,
                                   I2C_1_SS1_M_HSIOM_POS, I2C_1_SS1_M_HSIOM_SEL_GPIO);
#endif /* (I2C_1_SPI_MASTER_SS1_PIN) */

#if (I2C_1_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    I2C_1_ss2_m_Write(I2C_1_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    I2C_1_SET_HSIOM_SEL(I2C_1_SS2_M_HSIOM_REG, I2C_1_SS2_M_HSIOM_MASK,
                                   I2C_1_SS2_M_HSIOM_POS, I2C_1_SS2_M_HSIOM_SEL_GPIO);
#endif /* (I2C_1_SPI_MASTER_SS2_PIN) */

#if (I2C_1_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    I2C_1_ss3_m_Write(I2C_1_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    I2C_1_SET_HSIOM_SEL(I2C_1_SS3_M_HSIOM_REG, I2C_1_SS3_M_HSIOM_MASK,
                                   I2C_1_SS3_M_HSIOM_POS, I2C_1_SS3_M_HSIOM_SEL_GPIO);
#endif /* (I2C_1_SPI_MASTER_SS3_PIN) */

    #if (I2C_1_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        I2C_1_IntrTxMask = LO16(I2C_1_GetTxInterruptMode() & I2C_1_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        I2C_1_IntrTxMask = LO16(I2C_1_GetTxInterruptMode() & I2C_1_INTR_SPIS_TX_RESTORE);
    #endif /* (I2C_1_SPI_MASTER_CONST) */

#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (I2C_1_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: I2C_1_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - I2C_1_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - I2C_1_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - I2C_1_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - I2C_1_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void I2C_1_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = I2C_1_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~I2C_1_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  I2C_1_GET_SPI_CTRL_SS(slaveSelect);

        I2C_1_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (I2C_1_SPI_MASTER_CONST) */


#if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: I2C_1_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - I2C_1_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - I2C_1_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - I2C_1_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - I2C_1_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - I2C_1_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - I2C_1_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void I2C_1_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = I2C_1_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            I2C_1_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            I2C_1_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */


#if(I2C_1_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: I2C_1_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void I2C_1_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        I2C_1_ClearSpiExtClkInterruptSource(I2C_1_INTR_SPI_EC_WAKE_UP);
        I2C_1_SetSpiExtClkInterruptMode(I2C_1_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void I2C_1_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        I2C_1_SetSpiExtClkInterruptMode(I2C_1_NO_INTR_SOURCES);
    }
#endif /* (I2C_1_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
