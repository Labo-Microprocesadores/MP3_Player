/*
 * LCD_GDM1602A.c
 *
 *  Created on: 16 ene. 2021
 *      Author: Santi
 */


#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_dspi.h"


#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

#define LCD_SPI_BASEADDR   SPI0
#define LCD_SPI_CLK_SRC    DSPI0_CLK_SRC
#define LCD_SPI_CLK_FREQ   CLOCK_GetFreq(DSPI0_CLK_SRC)
#define LCD_SPI_PCS        kDSPI_Pcs0

#define TRANSFER_SIZE     256U    /*! Transfer dataSize */

#define EXAMPLE_DSPI_MASTER_IRQHandler SPI0_IRQHandler
#define EXAMPLE_DSPI_MASTER_IRQ        SPI0_IRQn

/* SPI related stuff */
static uint8_t lcdTxData[TRANSFER_SIZE] = {0U};
static uint32_t lcdTxCount;
static uint32_t lcdSpiCommand;
static uint32_t masterFifoSize;
static dspi_master_handle_t g_m_handle;
static bool spiTransferCompleted = false;

/*void SPI0_IRQHandler(void)
{

}*/


void LCD_Init(void)
{
	CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */

	PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2);            /* PORTD0 (pin 93) is configured as SPI0_PCS0 */
	PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2);            /* PORTD1 (pin 94) is configured as SPI0_SCK */
	PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2);            /* PORTD2 (pin 95) is configured as SPI0_SOUT */
	PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAlt2);            /* PORTD3 (pin 96) is configured as SPI0_SIN */

	uint32_t srcClock_Hz;
	uint32_t i;
	dspi_master_config_t masterConfig;

	SPI_MasterGetDefaultConfig(&masterConfig);

}
