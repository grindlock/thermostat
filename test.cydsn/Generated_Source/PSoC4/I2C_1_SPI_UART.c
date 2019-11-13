/***************************************************************************//**
* \file I2C_1_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 I2C_1_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 I2C_1_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  I2C_1_rxBufferOverflow;
    /** \} globals */
#endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

#if(I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 I2C_1_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 I2C_1_txBufferTail;
#endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

#if(I2C_1_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 I2C_1_rxBufferInternal[I2C_1_INTERNAL_RX_BUFFER_SIZE];
#endif /* (I2C_1_INTERNAL_RX_SW_BUFFER) */

#if(I2C_1_INTERNAL_TX_SW_BUFFER)
    volatile uint8 I2C_1_txBufferInternal[I2C_1_TX_BUFFER_SIZE];
#endif /* (I2C_1_INTERNAL_TX_SW_BUFFER) */


#if(I2C_1_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: I2C_1_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  I2C_1_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  I2C_1_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 I2C_1_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

        if (I2C_1_CHECK_RX_SW_BUFFER)
        {
            if (I2C_1_rxBufferHead != I2C_1_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (I2C_1_rxBufferTail + 1u);

                if (I2C_1_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = I2C_1_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                I2C_1_rxBufferTail = locTail;

                if (I2C_1_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (I2C_1_INTR_RX_MASK_REG & I2C_1_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        I2C_1_INTR_RX_MASK_REG |= I2C_1_INTR_RX_NOT_EMPTY;
                    }
                }
                

            }
        }
        else
        {
            /* Read data from RX FIFO */
            rxData = I2C_1_RX_FIFO_RD_REG;
        }
        

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  I2C_1_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  I2C_1_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 I2C_1_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

        if (I2C_1_CHECK_RX_SW_BUFFER)
        {
            locHead = I2C_1_rxBufferHead;

            if(locHead >= I2C_1_rxBufferTail)
            {
                size = (locHead - I2C_1_rxBufferTail);
            }
            else
            {
                size = (locHead + (I2C_1_INTERNAL_RX_BUFFER_SIZE - I2C_1_rxBufferTail));
            }
        }
        else
        {
            size = I2C_1_GET_RX_FIFO_ENTRIES;
        }
        

        return (size);
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  I2C_1_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  I2C_1_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void I2C_1_SpiUartClearRxBuffer(void)
    {
        if (I2C_1_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            I2C_1_DisableInt();

            /* Flush RX software buffer */
            I2C_1_rxBufferHead = I2C_1_rxBufferTail;
            I2C_1_rxBufferOverflow = 0u;

            I2C_1_CLEAR_RX_FIFO;
            I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_ALL);

            if (I2C_1_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                I2C_1_INTR_RX_MASK_REG |= I2C_1_INTR_RX_NOT_EMPTY;
            }
            
            
            /* Release lock */
            I2C_1_EnableInt();
        }
        else
        {
            I2C_1_CLEAR_RX_FIFO;
        }
        
    }

#endif /* (I2C_1_RX_DIRECTION) */


#if(I2C_1_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: I2C_1_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  I2C_1_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  I2C_1_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void I2C_1_SpiUartWriteTxData(uint32 txData)
    {
    #if (I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

        if (I2C_1_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((I2C_1_txBufferHead == I2C_1_txBufferTail) &&
                (I2C_1_SPI_UART_FIFO_SIZE != I2C_1_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                I2C_1_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (I2C_1_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (I2C_1_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == I2C_1_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_NOT_FULL);

                I2C_1_PutWordInTxBuffer(locHead, txData);

                I2C_1_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (I2C_1_INTR_TX_MASK_REG & I2C_1_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    I2C_1_INTR_TX_MASK_REG |= (uint32) I2C_1_INTR_TX_NOT_FULL;
                }
            }
        }
        else
        {
            /* Wait until TX FIFO has space to put data element */
            while (I2C_1_SPI_UART_FIFO_SIZE == I2C_1_GET_TX_FIFO_ENTRIES)
            {
            }

            I2C_1_TX_FIFO_WR_REG = txData;
        }
        
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  I2C_1_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  I2C_1_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void I2C_1_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            I2C_1_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  I2C_1_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  I2C_1_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 I2C_1_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

        if (I2C_1_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = I2C_1_txBufferTail;

            if (I2C_1_txBufferHead >= locTail)
            {
                size = (I2C_1_txBufferHead - locTail);
            }
            else
            {
                size = (I2C_1_txBufferHead + (I2C_1_TX_BUFFER_SIZE - locTail));
            }
        }
        else
        {
            size = I2C_1_GET_TX_FIFO_ENTRIES;
        }
        

        return (size);
    }


    /*******************************************************************************
    * Function Name: I2C_1_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  I2C_1_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  I2C_1_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void I2C_1_SpiUartClearTxBuffer(void)
    {
        if (I2C_1_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            I2C_1_DisableInt();

            /* Flush TX software buffer */
            I2C_1_txBufferHead = I2C_1_txBufferTail;

            I2C_1_INTR_TX_MASK_REG &= (uint32) ~I2C_1_INTR_TX_NOT_FULL;
            I2C_1_CLEAR_TX_FIFO;
            I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_ALL);

            /* Release lock */
            I2C_1_EnableInt();
        }
        else
        {
            I2C_1_CLEAR_TX_FIFO;
        }
        
    }

#endif /* (I2C_1_TX_DIRECTION) */


/*******************************************************************************
* Function Name: I2C_1_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 I2C_1_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = I2C_1_GetRxInterruptMode();

    I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: I2C_1_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 I2C_1_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = I2C_1_GetTxInterruptMode();

    I2C_1_SetTxInterruptMode(I2C_1_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: I2C_1_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void I2C_1_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (I2C_1_ONE_BYTE_WIDTH == I2C_1_rxDataBits)
        {
            I2C_1_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            I2C_1_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            I2C_1_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: I2C_1_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 I2C_1_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (I2C_1_ONE_BYTE_WIDTH == I2C_1_rxDataBits)
        {
            value = I2C_1_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) I2C_1_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)I2C_1_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: I2C_1_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void I2C_1_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (I2C_1_ONE_BYTE_WIDTH == I2C_1_txDataBits)
        {
            I2C_1_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            I2C_1_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            I2C_1_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: I2C_1_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 I2C_1_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (I2C_1_ONE_BYTE_WIDTH == I2C_1_txDataBits)
        {
            value = (uint32) I2C_1_txBuffer[idx];
        }
        else
        {
            value  = (uint32) I2C_1_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) I2C_1_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
