/***************************************************************************//**
* \file I2C_1_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_PVT.h"
#include "I2C_1_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (I2C_1_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: I2C_1_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(I2C_1_SPI_UART_ISR)
{
#if (I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

#if (I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef I2C_1_SPI_UART_ISR_ENTRY_CALLBACK
    I2C_1_SPI_UART_ISR_EntryCallback();
#endif /* I2C_1_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != I2C_1_customIntrHandler)
    {
        I2C_1_customIntrHandler();
    }

    if(I2C_1_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        I2C_1_ClearSpiExtClkInterruptSource(I2C_1_INTR_SPI_EC_WAKE_UP);
    }
    

    if (I2C_1_CHECK_RX_SW_BUFFER)
    {
        if (I2C_1_CHECK_INTR_RX_MASKED(I2C_1_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (I2C_1_rxBufferHead + 1u);

                /* Adjust local head index */
                if (I2C_1_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == I2C_1_rxBufferTail)
                {
                    if (I2C_1_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        I2C_1_INTR_RX_MASK_REG &= ~I2C_1_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    else
                    {
                        /* Overflow: through away received data element */
                        (void) I2C_1_RX_FIFO_RD_REG;
                        I2C_1_rxBufferOverflow = (uint8) I2C_1_INTR_RX_OVERFLOW;
                    }
                    
                }
                else
                {
                    /* Store received data */
                    I2C_1_PutWordInRxBuffer(locHead, I2C_1_RX_FIFO_RD_REG);

                    /* Move head index */
                    I2C_1_rxBufferHead = locHead;
                }
            }
            while(0u != I2C_1_GET_RX_FIFO_ENTRIES);

            I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);
        }
    }
    


    if (I2C_1_CHECK_TX_SW_BUFFER)
    {
        if (I2C_1_CHECK_INTR_TX_MASKED(I2C_1_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (I2C_1_txBufferHead != I2C_1_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (I2C_1_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (I2C_1_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    I2C_1_TX_FIFO_WR_REG = I2C_1_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    I2C_1_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    I2C_1_DISABLE_INTR_TX(I2C_1_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (I2C_1_SPI_UART_FIFO_SIZE != I2C_1_GET_TX_FIFO_ENTRIES);

            I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_NOT_FULL);
        }
    }
    

#ifdef I2C_1_SPI_UART_ISR_EXIT_CALLBACK
    I2C_1_SPI_UART_ISR_ExitCallback();
#endif /* I2C_1_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (I2C_1_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
