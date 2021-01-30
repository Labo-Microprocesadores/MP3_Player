/***************************************************************************/ /**
  @file     matrix display.c
  @brief    8x8 RGB display source
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/******************************************************************************
 * 		INCLUDES HEADER FILES
 ****************************************************************************/
#include "fsl_edma.h"
#include "fsl_dmamux.h"

#include "ftm.h"
#include "board.h"
#include "matrix_display.h"
#include "MK64F12.h"

/***************************************************************************
*	CONSTANT AND MACRO DEFINITIONS
****************************************************************************/

#define PIXEL_SIZE (24U)
#define DMA_CHANEL (1U)

#define ZERO 	(10U)
#define ONE 	(20U)
#define PULSE 	(29U) // 30 - 1

/***************************************************************************
*	LOCAL VARIABLES WITH FILE LEVEL SCOPE
****************************************************************************/
static uint16_t buffers[2][DISPLAY_SIZE * PIXEL_SIZE + 1];
static uint16_t * currBuffer;

static pixel_t pixel_buffer[DISPLAY_SIZE];
static bool change_buffer = false;
static uint8_t bright = 2;
static bool on = true;

static edma_handle_t g_EDMA_Handle;                             /* Edma handler */
static edma_transfer_config_t g_transferConfig;                 /* Edma transfer config. */

/***************************************************************************
*	LOCAL FUNCTION DECLARATION
****************************************************************************/

static void md_dmaCallback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);

/***************************************************************************
*	GLOBAL FUNCTION DEFINITIONS
****************************************************************************/

void md_Init(void)
{
	buffers[0][0] = 2;
	buffers[1][0] = 2;
	for (int i = 1; i <= DISPLAY_SIZE * PIXEL_SIZE; i++)
	{
		buffers[0][i] = ZERO;
		buffers[1][i] = ZERO;
	}
	currBuffer = buffers[0];

	PWM_Init(0, FTM_CH_0, FTM_PSC_x2, 2, 1, 4, FTM_lAssertedHigh, PULSE, ZERO, FTM_DMA_ON);

	DMAMUX_Init(DMAMUX);
	DMAMUX_SetSource(DMAMUX, DMA_CHANEL, FTM_DMA_SOURCE);

	edma_config_t userConfig;

	EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DMA0, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, DMA_CHANEL);
    EDMA_SetCallback(&g_EDMA_Handle, md_dmaCallback, NULL);

    EDMA_PrepareTransfer(&g_transferConfig, (void *)(currBuffer), sizeof(uint16_t),
                            (void *)FTM_GetCnVAddress(0, 0), sizeof(uint16_t),
							sizeof(uint16_t), (DISPLAY_SIZE * PIXEL_SIZE + 1)* sizeof(uint16_t) ,
							kEDMA_MemoryToPeripheral);

    EDMA_SetTransferConfig(DMA0, DMA_CHANEL, &g_transferConfig, NULL);
    EDMA_StartTransfer(&g_EDMA_Handle);
}

void md_writeBuffer(pixel_t *new_buffer)
{
	uint16_t i = 0;
	uint16_t * backBuffer = (currBuffer == buffers[0]) ? buffers[1]:buffers[0];

	for (i = 1; i <= DISPLAY_SIZE * PIXEL_SIZE; i++)
	{
		backBuffer[i] = ZERO;
	}

	for (i = 0; i < DISPLAY_SIZE; i++)
	{
		pixel_buffer[i] = new_buffer[i];

		backBuffer[i * 24 +  8 - bright] = new_buffer[i].G ? ONE : ZERO;
		backBuffer[i * 24 + 16 - bright] = new_buffer[i].R ? ONE : ZERO;
		backBuffer[i * 24 + 24 - bright] = new_buffer[i].B ? ONE : ZERO;
	}
	change_buffer = true;
}

pixel_t md_makeColor(bool r, bool g, bool b)
{

	pixel_t ret = {.R = r, .G = g, .B = b};
	return ret;
}

void md_setBrightness(uint8_t brigthness)
{
	uint8_t new_b = brigthness / 32;
	if(new_b == 0){new_b = 1;}
	if(new_b >= 7){new_b = 6;}
	if(bright != new_b)
	{
		bright = new_b;
		md_writeBuffer(pixel_buffer);
	}
}

/***************************************************************************
*	LOCAL FUNCTION DEFINITIONS
****************************************************************************/

static void md_dmaCallback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
	EDMA_ClearChannelStatusFlags(DMA0, DMA_CHANEL, kEDMA_InterruptFlag);
	while(!FTM_IsInterruptPending (0,FTM_CH_0)); // Sync with CHF

	if(on)
	{
		FTM_offOM(0,0);
		on = !on;
	}
	else
	{
		on = !on;
		FTM_onOM(0,0);
	}

	if(change_buffer)
	{
		if(currBuffer == buffers[0])
			currBuffer = buffers[1];
		else
			currBuffer = buffers[0];

		change_buffer = false;
	}

	EDMA_PrepareTransfer(&g_transferConfig, (void *)(currBuffer), sizeof(uint16_t),
	                            (void *)FTM_GetCnVAddress(0, 0), sizeof(uint16_t),
								sizeof(uint16_t), (DISPLAY_SIZE * PIXEL_SIZE + 1) * sizeof(uint16_t) ,
								kEDMA_MemoryToPeripheral);

	EDMA_SetTransferConfig(DMA0, DMA_CHANEL, &g_transferConfig, NULL);
	EDMA_StartTransfer(&g_EDMA_Handle);

}
