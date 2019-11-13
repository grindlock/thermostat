/***************************************************************************//**
* \file I2C_1_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "cyapicallbacks.h"

#if (I2C_1_UART_WAKE_ENABLE_CONST && I2C_1_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when I2C_1_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 I2C_1_skipStart = 1u;
    /** \} globals */
#endif /* (I2C_1_UART_WAKE_ENABLE_CONST && I2C_1_UART_RX_WAKEUP_IRQ) */

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const I2C_1_UART_INIT_STRUCT I2C_1_configUart =
    {
        I2C_1_UART_SUB_MODE,
        I2C_1_UART_DIRECTION,
        I2C_1_UART_DATA_BITS_NUM,
        I2C_1_UART_PARITY_TYPE,
        I2C_1_UART_STOP_BITS_NUM,
        I2C_1_UART_OVS_FACTOR,
        I2C_1_UART_IRDA_LOW_POWER,
        I2C_1_UART_MEDIAN_FILTER_ENABLE,
        I2C_1_UART_RETRY_ON_NACK,
        I2C_1_UART_IRDA_POLARITY,
        I2C_1_UART_DROP_ON_PARITY_ERR,
        I2C_1_UART_DROP_ON_FRAME_ERR,
        I2C_1_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        I2C_1_UART_MP_MODE_ENABLE,
        I2C_1_UART_MP_ACCEPT_ADDRESS,
        I2C_1_UART_MP_RX_ADDRESS,
        I2C_1_UART_MP_RX_ADDRESS_MASK,
        (uint32) I2C_1_SCB_IRQ_INTERNAL,
        I2C_1_UART_INTR_RX_MASK,
        I2C_1_UART_RX_TRIGGER_LEVEL,
        I2C_1_UART_INTR_TX_MASK,
        I2C_1_UART_TX_TRIGGER_LEVEL,
        (uint8) I2C_1_UART_BYTE_MODE_ENABLE,
        (uint8) I2C_1_UART_CTS_ENABLE,
        (uint8) I2C_1_UART_CTS_POLARITY,
        (uint8) I2C_1_UART_RTS_POLARITY,
        (uint8) I2C_1_UART_RTS_FIFO_LEVEL,
        (uint8) I2C_1_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: I2C_1_UartInit
    ****************************************************************************//**
    *
    *  Configures the I2C_1 for UART operation.
    *
    *  This function is intended specifically to be used when the I2C_1
    *  configuration is set to “Unconfigured I2C_1” in the customizer.
    *  After initializing the I2C_1 in UART mode using this function,
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
    void I2C_1_UartInit(const I2C_1_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (I2C_1_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (I2C_1_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

            /* Configure pins */
            I2C_1_SetPins(I2C_1_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            I2C_1_scbMode       = (uint8) I2C_1_SCB_MODE_UART;
            I2C_1_scbEnableWake = (uint8) config->enableWake;
            I2C_1_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            I2C_1_rxBuffer      =         config->rxBuffer;
            I2C_1_rxDataBits    = (uint8) config->dataBits;
            I2C_1_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            I2C_1_txBuffer      =         config->txBuffer;
            I2C_1_txDataBits    = (uint8) config->dataBits;
            I2C_1_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(I2C_1_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                I2C_1_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (I2C_1_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (I2C_1_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                I2C_1_CTRL_REG  = I2C_1_GET_CTRL_OVS(config->oversample);
            }

            I2C_1_CTRL_REG     |= I2C_1_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             I2C_1_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             I2C_1_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            I2C_1_UART_CTRL_REG = I2C_1_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            I2C_1_UART_RX_CTRL_REG = I2C_1_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        I2C_1_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        I2C_1_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        I2C_1_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        I2C_1_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        I2C_1_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(I2C_1_UART_PARITY_NONE != config->parity)
            {
               I2C_1_UART_RX_CTRL_REG |= I2C_1_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    I2C_1_UART_RX_CTRL_PARITY_ENABLED;
            }

            I2C_1_RX_CTRL_REG      = I2C_1_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                I2C_1_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                I2C_1_GET_UART_RX_CTRL_ENABLED(config->direction);

            I2C_1_RX_FIFO_CTRL_REG = I2C_1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            I2C_1_RX_MATCH_REG     = I2C_1_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                I2C_1_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            I2C_1_UART_TX_CTRL_REG = I2C_1_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                I2C_1_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(I2C_1_UART_PARITY_NONE != config->parity)
            {
               I2C_1_UART_TX_CTRL_REG |= I2C_1_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    I2C_1_UART_TX_CTRL_PARITY_ENABLED;
            }

            I2C_1_TX_CTRL_REG      = I2C_1_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                I2C_1_GET_UART_TX_CTRL_ENABLED(config->direction);

            I2C_1_TX_FIFO_CTRL_REG = I2C_1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            I2C_1_UART_FLOW_CTRL_REG = I2C_1_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            I2C_1_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            I2C_1_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            I2C_1_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (I2C_1_ISR_NUMBER);
            CyIntSetPriority(I2C_1_ISR_NUMBER, I2C_1_ISR_PRIORITY);
            (void) CyIntSetVector(I2C_1_ISR_NUMBER, &I2C_1_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(I2C_1_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (I2C_1_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(I2C_1_RX_WAKE_ISR_NUMBER, I2C_1_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(I2C_1_RX_WAKE_ISR_NUMBER, &I2C_1_UART_WAKEUP_ISR);
        #endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            I2C_1_INTR_I2C_EC_MASK_REG = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_SPI_EC_MASK_REG = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_SLAVE_MASK_REG  = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_MASTER_MASK_REG = I2C_1_NO_INTR_SOURCES;
            I2C_1_INTR_RX_MASK_REG     = config->rxInterruptMask;
            I2C_1_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            I2C_1_IntrTxMask = LO16(I2C_1_INTR_TX_MASK_REG);

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
    * Function Name: I2C_1_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void I2C_1_UartInit(void)
    {
        /* Configure UART interface */
        I2C_1_CTRL_REG = I2C_1_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        I2C_1_UART_CTRL_REG = I2C_1_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        I2C_1_UART_RX_CTRL_REG = I2C_1_UART_DEFAULT_UART_RX_CTRL;
        I2C_1_RX_CTRL_REG      = I2C_1_UART_DEFAULT_RX_CTRL;
        I2C_1_RX_FIFO_CTRL_REG = I2C_1_UART_DEFAULT_RX_FIFO_CTRL;
        I2C_1_RX_MATCH_REG     = I2C_1_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        I2C_1_UART_TX_CTRL_REG = I2C_1_UART_DEFAULT_UART_TX_CTRL;
        I2C_1_TX_CTRL_REG      = I2C_1_UART_DEFAULT_TX_CTRL;
        I2C_1_TX_FIFO_CTRL_REG = I2C_1_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        I2C_1_UART_FLOW_CTRL_REG = I2C_1_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(I2C_1_SCB_IRQ_INTERNAL)
        CyIntDisable    (I2C_1_ISR_NUMBER);
        CyIntSetPriority(I2C_1_ISR_NUMBER, I2C_1_ISR_PRIORITY);
        (void) CyIntSetVector(I2C_1_ISR_NUMBER, &I2C_1_SPI_UART_ISR);
    #endif /* (I2C_1_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(I2C_1_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (I2C_1_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(I2C_1_RX_WAKE_ISR_NUMBER, I2C_1_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(I2C_1_RX_WAKE_ISR_NUMBER, &I2C_1_UART_WAKEUP_ISR);
    #endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        I2C_1_INTR_I2C_EC_MASK_REG = I2C_1_UART_DEFAULT_INTR_I2C_EC_MASK;
        I2C_1_INTR_SPI_EC_MASK_REG = I2C_1_UART_DEFAULT_INTR_SPI_EC_MASK;
        I2C_1_INTR_SLAVE_MASK_REG  = I2C_1_UART_DEFAULT_INTR_SLAVE_MASK;
        I2C_1_INTR_MASTER_MASK_REG = I2C_1_UART_DEFAULT_INTR_MASTER_MASK;
        I2C_1_INTR_RX_MASK_REG     = I2C_1_UART_DEFAULT_INTR_RX_MASK;
        I2C_1_INTR_TX_MASK_REG     = I2C_1_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        I2C_1_IntrTxMask = LO16(I2C_1_INTR_TX_MASK_REG);

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
* Function Name: I2C_1_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void I2C_1_UartPostEnable(void)
{
#if (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (I2C_1_TX_SCL_MISO_PIN)
        if (I2C_1_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            I2C_1_SET_HSIOM_SEL(I2C_1_TX_SCL_MISO_HSIOM_REG, I2C_1_TX_SCL_MISO_HSIOM_MASK,
                                           I2C_1_TX_SCL_MISO_HSIOM_POS, I2C_1_TX_SCL_MISO_HSIOM_SEL_UART);
        }
    #endif /* (I2C_1_TX_SCL_MISO_PIN_PIN) */

    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        #if (I2C_1_RTS_SS0_PIN)
            if (I2C_1_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                I2C_1_SET_HSIOM_SEL(I2C_1_RTS_SS0_HSIOM_REG, I2C_1_RTS_SS0_HSIOM_MASK,
                                               I2C_1_RTS_SS0_HSIOM_POS, I2C_1_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (I2C_1_RTS_SS0_PIN) */
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#else
    #if (I2C_1_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_TX_HSIOM_REG, I2C_1_TX_HSIOM_MASK,
                                       I2C_1_TX_HSIOM_POS, I2C_1_TX_HSIOM_SEL_UART);
    #endif /* (I2C_1_UART_TX_PIN) */

    #if (I2C_1_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_RTS_HSIOM_REG, I2C_1_RTS_HSIOM_MASK,
                                       I2C_1_RTS_HSIOM_POS, I2C_1_RTS_HSIOM_SEL_UART);
    #endif /* (I2C_1_UART_RTS_PIN) */
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    I2C_1_SetTxInterruptMode(I2C_1_IntrTxMask);
}


/*******************************************************************************
* Function Name: I2C_1_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void I2C_1_UartStop(void)
{
#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (I2C_1_TX_SCL_MISO_PIN)
        if (I2C_1_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            I2C_1_SET_HSIOM_SEL(I2C_1_TX_SCL_MISO_HSIOM_REG, I2C_1_TX_SCL_MISO_HSIOM_MASK,
                                           I2C_1_TX_SCL_MISO_HSIOM_POS, I2C_1_TX_SCL_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (I2C_1_TX_SCL_MISO_PIN_PIN) */

    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        #if (I2C_1_RTS_SS0_PIN)
            if (I2C_1_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                I2C_1_uart_rts_spi_ss0_Write(I2C_1_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                I2C_1_SET_HSIOM_SEL(I2C_1_RTS_SS0_HSIOM_REG, I2C_1_RTS_SS0_HSIOM_MASK,
                                               I2C_1_RTS_SS0_HSIOM_POS, I2C_1_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (I2C_1_RTS_SS0_PIN) */
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#else
    #if (I2C_1_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_TX_HSIOM_REG, I2C_1_TX_HSIOM_MASK,
                                       I2C_1_TX_HSIOM_POS, I2C_1_TX_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_UART_TX_PIN) */

    #if (I2C_1_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        I2C_1_rts_Write(I2C_1_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        I2C_1_SET_HSIOM_SEL(I2C_1_RTS_HSIOM_REG, I2C_1_RTS_HSIOM_MASK,
                                       I2C_1_RTS_HSIOM_POS, I2C_1_RTS_HSIOM_SEL_GPIO);
    #endif /* (I2C_1_UART_RTS_PIN) */

#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (I2C_1_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    I2C_1_UART_RX_CTRL_REG &= (uint32) ~I2C_1_UART_RX_CTRL_SKIP_START;
#endif /* (I2C_1_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    I2C_1_IntrTxMask = LO16(I2C_1_GetTxInterruptMode() & I2C_1_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: I2C_1_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void I2C_1_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = I2C_1_RX_MATCH_REG;

    matchReg &= ((uint32) ~I2C_1_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & I2C_1_RX_MATCH_ADDR_MASK)); /* Set address  */

    I2C_1_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: I2C_1_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void I2C_1_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = I2C_1_RX_MATCH_REG;

    matchReg &= ((uint32) ~I2C_1_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << I2C_1_RX_MATCH_MASK_POS));

    I2C_1_RX_MATCH_REG = matchReg;
}


#if(I2C_1_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: I2C_1_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check I2C_1_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 I2C_1_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != I2C_1_SpiUartGetRxBufferSize())
        {
            rxData = I2C_1_SpiUartReadRxData();
        }

        if (I2C_1_CHECK_INTR_RX(I2C_1_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: I2C_1_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - I2C_1_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - I2C_1_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - I2C_1_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - I2C_1_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check I2C_1_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 I2C_1_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        if (I2C_1_CHECK_RX_SW_BUFFER)
        {
            I2C_1_DisableInt();
        }
        

        if (0u != I2C_1_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            if (I2C_1_CHECK_RX_SW_BUFFER)
            {
                I2C_1_EnableInt();
            }
            

            /* Get received byte */
            rxData = I2C_1_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = I2C_1_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            if (I2C_1_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);

                I2C_1_EnableInt();
            }
            
        }

        /* Get and clear RX error mask */
        tmpStatus = (I2C_1_GetRxInterruptSource() & I2C_1_INTR_RX_ERR);
        I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: I2C_1_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - I2C_1_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - I2C_1_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void I2C_1_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                I2C_1_UART_FLOW_CTRL_REG |= (uint32)  I2C_1_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                I2C_1_UART_FLOW_CTRL_REG &= (uint32) ~I2C_1_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: I2C_1_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void I2C_1_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = I2C_1_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~I2C_1_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (I2C_1_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            I2C_1_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#endif /* (I2C_1_UART_RX_DIRECTION) */


#if(I2C_1_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: I2C_1_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void I2C_1_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            I2C_1_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: I2C_1_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void I2C_1_UartPutCRLF(uint32 txDataByte)
    {
        I2C_1_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        I2C_1_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        I2C_1_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: I2C_1SCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void I2C_1_UartEnableCts(void)
        {
            I2C_1_UART_FLOW_CTRL_REG |= (uint32)  I2C_1_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: I2C_1_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void I2C_1_UartDisableCts(void)
        {
            I2C_1_UART_FLOW_CTRL_REG &= (uint32) ~I2C_1_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: I2C_1_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - I2C_1_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - I2C_1_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void I2C_1_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                I2C_1_UART_FLOW_CTRL_REG |= (uint32)  I2C_1_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                I2C_1_UART_FLOW_CTRL_REG &= (uint32) ~I2C_1_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: I2C_1_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void I2C_1_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = I2C_1_GetTxInterruptMode();
        I2C_1_SetTxInterruptMode(0u);
        I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = I2C_1_TX_CTRL_REG;

        /* Set break width */
        I2C_1_TX_CTRL_REG = (I2C_1_TX_CTRL_REG & (uint32) ~I2C_1_TX_CTRL_DATA_WIDTH_MASK) |
                                        I2C_1_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        I2C_1_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (I2C_1_GetTxInterruptSource() & I2C_1_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        I2C_1_TX_CTRL_REG = txCtrlReg;
        I2C_1_SetTxInterruptMode(txIntrReg);
    }
#endif /* (I2C_1_UART_TX_DIRECTION) */


#if (I2C_1_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: I2C_1_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void I2C_1_UartSaveConfig(void)
    {
    #if (I2C_1_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != I2C_1_skipStart)
        {
            I2C_1_UART_RX_CTRL_REG |= (uint32)  I2C_1_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            I2C_1_UART_RX_CTRL_REG &= (uint32) ~I2C_1_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        I2C_1_CLEAR_UART_RX_WAKE_INTR;
        I2C_1_RxWakeClearPendingInt();
        I2C_1_RxWakeEnableInt();
    #endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: I2C_1_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void I2C_1_UartRestoreConfig(void)
    {
    #if (I2C_1_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        I2C_1_RxWakeDisableInt();
    #endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */
    }


    #if (I2C_1_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: I2C_1_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(I2C_1_UART_WAKEUP_ISR)
        {
        #ifdef I2C_1_UART_WAKEUP_ISR_ENTRY_CALLBACK
            I2C_1_UART_WAKEUP_ISR_EntryCallback();
        #endif /* I2C_1_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            I2C_1_CLEAR_UART_RX_WAKE_INTR;

        #ifdef I2C_1_UART_WAKEUP_ISR_EXIT_CALLBACK
            I2C_1_UART_WAKEUP_ISR_ExitCallback();
        #endif /* I2C_1_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */
#endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
