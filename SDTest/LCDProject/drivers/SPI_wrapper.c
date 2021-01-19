/*
 * SPI_wrapper.c
 *
 *  Created on: 16 ene. 2021
 *      Author: Santi
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_dspi.h"

#define MAX_SIZE 200
#define MSG_LEN(r,f,m) (((r)+(m)-(f)) % ((m) - 1 )) // MSG_LEN(rear, front, max_len)

static SPI_Type * p_spi[] = SPI_BASE_PTRS;

static uint8_t buffer_out[MAX_SIZE] = {0U};
static uint8_t p_out_rear = 0, p_out_front = 1;
static uint32_t masterCommand;
static uint32_t masterFifoSize;


void SPI_Init(spi_id_t id, spi_slave_t slave, uint32_t baudrate)
{
	/* Clock Gate Control: Clock enabled */
	if(id == 0)
	{
		CLOCK_EnableClock(kCLOCK_PortD);
		if(slave > 0 && slave < 5)
			CLOCK_EnableClock(kCLOCK_PortC);
		else if(slave == 0)
			CLOCK_EnableClock(kCLOCK_PortB);
	}
	else
		CLOCK_EnableClock(kCLOCK_PortB);

	/* Pin routing */
	PORT_Type * port_spi_n = id == 0?PORTD:PORTB;
	uint8_t sck = id == 0?1:2, sout = id == 0?2:16, sin = id == 0?3:17;

	PORT_SetPinMux(port_spi_n, sck, kPORT_MuxAlt2);
	PORT_SetPinMux(port_spi_n, sout, kPORT_MuxAlt2);
	PORT_SetPinMux(port_spi_n, sin, kPORT_MuxAlt2);

	if(id != 0)
		PORT_SetPinMux(PORTB, 3, kPORT_MuxAlt2);            /* PORTD0 (pin 93) is configured as SPI0_PCS0 */
	else if(slave > 0 && slave < 5)
	{
		PORT_SetPinMux(PORTC, slave - 1, kPORT_MuxAlt2);
		slave = 5 - slave;
	}
	else if(slave != 0)
	{
		PORT_SetPinMux(PORTB, slave, kPORT_MuxAlt2);
		slave = 5;
	}
	else
		PORT_SetPinMux(PORTD, slave, kPORT_MuxAlt2);

	/* SPI Config */

	dspi_master_config_t masterConfig;

	DSPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.whichPcs = 1<<slave;
	masterConfig.ctarConfig.baudRate = baudrate;

	uint32_t srcClock_Hz = CLOCK_GetFreq(BUS_CLK);
	DSPI_MasterInit(p_spi[id], &masterConfig, srcClock_Hz);

	/* Enable the NVIC for DSPI peripheral. */
	EnableIRQ(SPI0_IRQn + id != 2?id:39);

	/* Start master transfer*/
	dspi_command_data_config_t commandData;
	commandData.isPcsContinuous    = false;
	commandData.whichCtar          = kDSPI_Ctar0;
	commandData.whichPcs           = 1<<slave;;
	commandData.isEndOfQueue       = false;
	commandData.clearTransferCount = false;

	masterCommand = DSPI_MasterGetFormattedCommand(&commandData);

	masterFifoSize = FSL_FEATURE_DSPI_FIFO_SIZEn(port_spi_n);

	DSPI_StopTransfer(port_spi_n);
	DSPI_FlushFifo(port_spi_n, true, true);
	DSPI_ClearStatusFlags(port_spi_n, (uint32_t)kDSPI_AllStatusFlag);

}

void SPI0_IRQHandler(void)
{
    /*if (masterRxCount < TRANSFER_SIZE)
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
    }*/

    if (MSG_LEN(p_out_rear, p_out_front, MAX_SIZE) != 0)
    {
        while ((DSPI_GetStatusFlags(p_spi[0]) & kDSPI_TxFifoFillRequestFlag) &&
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

            /* Try to clear the TFFF; if the TX FIFO is full this will clear */
            DSPI_ClearStatusFlags(EXAMPLE_DSPI_MASTER_BASEADDR, kDSPI_TxFifoFillRequestFlag);
        }
    }

    /* Check if we're done with this transfer.*/
    if ((masterTxCount == TRANSFER_SIZE) && (masterRxCount == TRANSFER_SIZE))
    {
    	isTransferCompleted = true;
        /* Complete the transfer and disable the interrupts */
        DSPI_DisableInterrupts(EXAMPLE_DSPI_MASTER_BASEADDR,
                               kDSPI_RxFifoDrainRequestInterruptEnable | kDSPI_TxFifoFillRequestInterruptEnable);
    }
    SDK_ISR_EXIT_BARRIER;
}


