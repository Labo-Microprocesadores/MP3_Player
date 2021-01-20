/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_dspi.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_DSPI_MASTER_BASEADDR   SPI0
#define EXAMPLE_DSPI_MASTER_CLK_SRC    DSPI0_CLK_SRC
#define EXAMPLE_DSPI_MASTER_CLK_FREQ   CLOCK_GetFreq(DSPI0_CLK_SRC)
#define EXAMPLE_DSPI_MASTER_IRQ        SPI0_IRQn
#define EXAMPLE_DSPI_MASTER_PCS        kDSPI_Pcs0
#define EXAMPLE_DSPI_MASTER_IRQHandler SPI0_IRQHandler

#define EXAMPLE_DSPI_SLAVE_BASEADDR   SPI1
#define EXAMPLE_DSPI_SLAVE_IRQ        SPI1_IRQn
#define EXAMPLE_DSPI_SLAVE_IRQHandler SPI1_IRQHandler
#define TRANSFER_SIZE     256U    /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 500000U /*! Transfer baudrate - 500k */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t masterRxData[TRANSFER_SIZE] = {0U};
uint8_t masterTxData[TRANSFER_SIZE] = {0U};

volatile uint32_t masterTxCount;
volatile uint32_t masterRxCount;
volatile uint32_t masterCommand;
uint32_t masterFifoSize;

dspi_master_handle_t g_m_handle;
volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
#ifdef TEST

void SPI0_IRQHandler(void)
{
    if (masterRxCount < TRANSFER_SIZE)
    {
        while (DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_RxFifoDrainRequestFlag)
        {
            masterRxData[masterRxCount] = DSPI_ReadData(EXAMPLE_DSPI_MASTER_BASEADDR);
            ++masterRxCount;

            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_RxFifoDrainRequestFlag);

            if (masterRxCount == TRANSFER_SIZE)
            {
                break;
            }
        }
    }

    if (masterTxCount < TRANSFER_SIZE)
    {
        while ((DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_TxFifoFillRequestFlag) &&
               ((masterTxCount - masterRxCount) < masterFifoSize))
        {
            if (masterTxCount < TRANSFER_SIZE)
            {
                EXAMPLE_DSPI_MASTER_BASEADDR->PUSHR = masterCommand | masterTxData[masterTxCount];
                ++masterTxCount;
            }
            else
            {
                break;
            }

            // Try to clear the TFFF; if the TX FIFO is full this will clear
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }
    }

    // Check if we're done with this transfer.
    if ((masterTxCount == TRANSFER_SIZE) && (masterRxCount == TRANSFER_SIZE))
    {
    	isTransferCompleted = true;
        // Complete the transfer and disable the interrupts
        DSPI_DisableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR,
                               kDSPI_RxFifoDrainRequestInterruptEnable | kDSPI_TxFifoFillRequestInterruptEnable);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    uint32_t srcClock_Hz;
    uint32_t errorCount;
    uint32_t i;
    dspi_master_config_t masterConfig;

    /* Master config */
    masterConfig.whichCtar                                = kDSPI_Ctar0;
    masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.bitsPerFrame                  = 8;
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;

    masterConfig.whichPcs           = EXAMPLE_DSPI_MASTER_PCS;
    masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

    masterConfig.enableContinuousSCK        = false;
    masterConfig.enableRxFifoOverWrite      = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

    srcClock_Hz = EXAMPLE_DSPI_MASTER_CLK_FREQ;
    DSPI_MasterInit(EXAMPLE_DSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);

    /* Set dspi slave interrupt priority higher. */
    NVIC_SetPriority(EXAMPLE_DSPI_MASTER_IRQ, 1U);

    /* Set up the transfer data */
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        masterTxData[i] = i % 256U;
        masterRxData[i] = 0U;

    }

    isTransferCompleted = false;

    /* Enable the NVIC for DSPI peripheral. */
    EnableIRQ(EXAMPLE_DSPI_MASTER_IRQ);

    /* Start master transfer*/
    dspi_command_data_config_t commandData;
    commandData.isPcsContinuous    = false;
    commandData.whichCtar          = kDSPI_Ctar0;
    commandData.whichPcs           = EXAMPLE_DSPI_MASTER_PCS;
    commandData.isEndOfQueue       = false;
    commandData.clearTransferCount = false;

    masterCommand = DSPI_MasterGetFormattedCommand(&commandData);

    masterFifoSize = FSL_FEATURE_DSPI_FIFO_SIZEn(EXAMPLE_DSPI_MASTER_BASEADDR);
    masterTxCount  = 0;
    masterRxCount  = 0;

    DSPI_StopTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);
    DSPI_FlushFifo(EXAMPLE_DSPI_MASTER_BASEADDR, true, true);
    DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, (uint32_t)kDSPI_AllStatusFlag);

    /*Fill up the master Tx data*/
    while (DSPI_GetStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR) & kDSPI_TxFifoFillRequestFlag)
    {
        if (masterTxCount < TRANSFER_SIZE)
        {
            DSPI_MasterWriteData(EXAMPLE_DSPI_MASTER_BASEADDR, &commandData, masterTxData[masterTxCount]);
            ++masterTxCount;
        }
        else
        {
            break;
        }

        /* Try to clear the TFFF; if the TX FIFO is full this will clear */
        DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
    }

    /*Enable master RX interrupt*/
	DSPI_EnableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_RxFifoDrainRequestInterruptEnable);
    /* Start DSPI transafer.*/
    DSPI_StartTransfer(EXAMPLE_DSPI_MASTER_BASEADDR);

    /* Wait slave received all data. */
    while (!isTransferCompleted)
    {
    }

    errorCount = 0U;
    for (i = 0U; i < TRANSFER_SIZE; i++)
    {
        if (masterTxData[i] != masterRxData[i])
        {
            errorCount++;
        }

    }
    if (errorCount == 0U)
    {
        PRINTF(" \r\nDSPI transfer all data matched! \r\n");
    }
    else
    {
        PRINTF(" \r\nError occurred in DSPI transfer ! \r\n");
    }

    DSPI_Deinit(EXAMPLE_DSPI_MASTER_BASEADDR);

    while (1)
    {
    }
}
#endif
