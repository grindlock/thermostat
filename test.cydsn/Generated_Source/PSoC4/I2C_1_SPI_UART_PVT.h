/***************************************************************************//**
* \file I2C_1_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_I2C_1_H)
#define CY_SCB_SPI_UART_PVT_I2C_1_H

#include "I2C_1_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  I2C_1_rxBufferHead;
    extern volatile uint32  I2C_1_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   I2C_1_rxBufferOverflow;
    /** @} globals */
#endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

#if (I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  I2C_1_txBufferHead;
    extern volatile uint32  I2C_1_txBufferTail;
#endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

#if (I2C_1_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 I2C_1_rxBufferInternal[I2C_1_INTERNAL_RX_BUFFER_SIZE];
#endif /* (I2C_1_INTERNAL_RX_SW_BUFFER) */

#if (I2C_1_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 I2C_1_txBufferInternal[I2C_1_TX_BUFFER_SIZE];
#endif /* (I2C_1_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void I2C_1_SpiPostEnable(void);
void I2C_1_SpiStop(void);

#if (I2C_1_SCB_MODE_SPI_CONST_CFG)
    void I2C_1_SpiInit(void);
#endif /* (I2C_1_SCB_MODE_SPI_CONST_CFG) */

#if (I2C_1_SPI_WAKE_ENABLE_CONST)
    void I2C_1_SpiSaveConfig(void);
    void I2C_1_SpiRestoreConfig(void);
#endif /* (I2C_1_SPI_WAKE_ENABLE_CONST) */

void I2C_1_UartPostEnable(void);
void I2C_1_UartStop(void);

#if (I2C_1_SCB_MODE_UART_CONST_CFG)
    void I2C_1_UartInit(void);
#endif /* (I2C_1_SCB_MODE_UART_CONST_CFG) */

#if (I2C_1_UART_WAKE_ENABLE_CONST)
    void I2C_1_UartSaveConfig(void);
    void I2C_1_UartRestoreConfig(void);
#endif /* (I2C_1_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in I2C_1_SetPins() */
#define I2C_1_UART_RX_PIN_ENABLE    (I2C_1_UART_RX)
#define I2C_1_UART_TX_PIN_ENABLE    (I2C_1_UART_TX)

/* UART RTS and CTS position to be used in  I2C_1_SetPins() */
#define I2C_1_UART_RTS_PIN_ENABLE    (0x10u)
#define I2C_1_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define I2C_1_SpiUartEnableIntRx(intSourceMask)  I2C_1_SetRxInterruptMode(intSourceMask)
#define I2C_1_SpiUartEnableIntTx(intSourceMask)  I2C_1_SetTxInterruptMode(intSourceMask)
uint32  I2C_1_SpiUartDisableIntRx(void);
uint32  I2C_1_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_I2C_1_H) */


/* [] END OF FILE */
