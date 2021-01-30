/***************************************************************************/ /**
  @file     dma.c
  @brief    DMA driver
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#include "dma.h"
#include "MK64F12.h"

#define DMA_CHANNELS 15

static void (*callbacks[DMA_CHANNELS])(void);

void DMA_Init(uint8_t channel, uint8_t dma_source, uint32_t source,
			  uint32_t dest, uint8_t src_offset, uint8_t dest_offset,
			  DMASize_t src_size, DMASize_t dest_size, uint32_t minorl_size,
			  uint32_t mayorL_size, int16_t ret_after_ML, void (*callback)(void))
{

	/* Enable the clock for the eDMA and the DMAMUX. */
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	/* Enable the eDMA channel 0 and set the FTM CH0 as the DMA request source. */
	DMAMUX->CHCFG[channel] |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(dma_source);
	/* Clear all the pending events. */
	NVIC_ClearPendingIRQ(DMA0_IRQn + channel);
	/* Enable the DMA interrupts. */
	NVIC_EnableIRQ(DMA0_IRQn + channel);

	/* Set memory address for source and destination. */
	DMA0->TCD[channel].SADDR = source;
	DMA0->TCD[channel].DADDR = dest;

	/* Set an offset for source and destination address. */
	DMA0->TCD[channel].SOFF = src_offset;
	DMA0->TCD[channel].DOFF = dest_offset;

	DMA0->TCD[channel].ATTR = DMA_ATTR_SSIZE(src_size) | DMA_ATTR_DSIZE(dest_size);

	/*Number of bytes to be transfered in each service request of the channel.*/
	DMA0->TCD[channel].NBYTES_MLNO = minorl_size; //* (1<<src_size);

	/* Autosize for Current major iteration count */
	DMA0->TCD[channel].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(mayorL_size);
	DMA0->TCD[channel].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(mayorL_size);

	DMA0->TCD[channel].SLAST = ret_after_ML;

	/* DLASTSGA DLAST Scatter and Gatter */
	DMA0->TCD[channel].DLAST_SGA = 0x00; // NOT EDITABLE FOR NOW

	/* Setup control and status register. */
	DMA0->TCD[channel].CSR = DMA_CSR_INTMAJOR_MASK; //Enable Major Interrupt.

	/* Enable request signal for channel 0. */
	DMA0->ERQ = DMA_ERQ_ERQ0_MASK << channel;

	callbacks[channel] = callback;
}

/* The red LED is toggled when an error occurs. */
void DMA_Error_IRQHandler()
{
	/* Clear the error interrupt flag.*/
	DMA0->CERR |= 0;

	/* Turn the red LED on. */
	//PTB->PTOR |= (1 << PIN_RED_LED);
}

void DMA0_IRQHandler()
{
	/* Clear the interrupt flag. */
	DMA0->CINT |= 0;
	callbacks[0]();
}

// Copiar y pegar si se necsita otra...
