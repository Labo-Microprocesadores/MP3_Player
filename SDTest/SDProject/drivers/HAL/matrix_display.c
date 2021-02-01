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

#include "gpio.h"
#include "SysTick.h"

/***************************************************************************
*	CONSTANT AND MACRO DEFINITIONS
****************************************************************************/

#define PIXEL_SIZE (24U)
#define DMA_CHANEL (0U)

#define FTM_PRESCALE   0                                               // Configuration of the FTM driver
#define FTM_MODULO     62                                              // for 800kbps rate needed in WS2812 leds
#define HIGH_DUTY      42                                              // Duty value for '1' binit
#define LOW_DUTY       20                                              // Duty value for '0' binit
#define OFF_DUTY	   1

#define PRE			(0U)
#define POST		(0U)
#define PIXELS		((DISPLAY_SIZE+8) * PIXEL_SIZE)
#define MATRIX_LEN	(PRE + PIXELS + POST)

#define ZERO 	LOW_DUTY//(10U)
#define ONE 	HIGH_DUTY//(20U)
#define PULSE 	(29U) // 30 - 1

/***************************************************************************
*	LOCAL VARIABLES WITH FILE LEVEL SCOPE
****************************************************************************/
static bool is_init = false;
static uint16_t buffers[2][MATRIX_LEN];
static uint16_t * currBuffer;

static pixel_t pixel_buffer[DISPLAY_SIZE];
static bool change_buffer = false;
static uint8_t bright = 0;

static edma_handle_t g_EDMA_Handle;                             /* Edma handler */
static edma_transfer_config_t g_transferConfig;                 /* Edma transfer config. */

static uint8_t timer_id;
static bool transfer_done = false;
/***************************************************************************
*	LOCAL FUNCTION DECLARATION
****************************************************************************/

static void md_dmaCallback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);
static void md_timerCallback(void);

/***************************************************************************
*	GLOBAL FUNCTION DEFINITIONS
****************************************************************************/

void md_Init(void)
{
	if(!is_init)
	{
		SysTick_Init();
		timer_id = SysTick_AddCallback(md_timerCallback, 2);
		Systick_PauseCallback(timer_id);

		for (int i = 0; i < PRE ; i++)
		{
			buffers[0][i] = OFF_DUTY;
			buffers[1][i] = OFF_DUTY;
		}
		for (int i = 0; i < PIXELS; i++)
		{
			buffers[0][i+PRE] = LOW_DUTY;
			buffers[1][i+PRE] = LOW_DUTY;
		}
		for(int i = 0; i < POST; i++)
		{
			buffers[0][i+PRE+PIXELS] = LOW_DUTY;
			buffers[1][i+PRE+PIXELS] = LOW_DUTY;
		}

		currBuffer = buffers[0];

		DMAMUX_Init(DMAMUX);
		DMAMUX_SetSource(DMAMUX, DMA_CHANEL, FTM_DMA_SOURCE);
		DMAMUX_EnableChannel(DMAMUX, DMA_CHANEL);
		edma_config_t userConfig;

		EDMA_GetDefaultConfig(&userConfig);
		EDMA_Init(DMA0, &userConfig);
		EDMA_CreateHandle(&g_EDMA_Handle, DMA0, DMA_CHANEL);
		EDMA_SetCallback(&g_EDMA_Handle, md_dmaCallback, NULL);

		PWM_Init(0, FTM_CH_0, FTM_PSC_x1, 2, 1, 4, FTM_lAssertedHigh,
				FTM_MODULO, LOW_DUTY, FTM_DMA_ON);

		EDMA_PrepareTransfer(&g_transferConfig, (void *)(currBuffer), sizeof(uint16_t),
								(void *)FTM_GetCnVAddress(0, 0), sizeof(uint16_t),
								sizeof(uint16_t), (MATRIX_LEN)* sizeof(uint16_t) ,
								kEDMA_MemoryToPeripheral);

		EDMA_SubmitTransfer(&g_EDMA_Handle, &g_transferConfig);
		//EDMA_SetTransferConfig(DMA0, DMA_CHANEL, &g_transferConfig, NULL);
		EDMA_EnableChannelInterrupts(DMA0, DMA_CHANEL, kEDMA_MajorInterruptEnable);

		EDMA_DisableChannelRequest(DMA0, DMA_CHANEL);
		EDMA_StartTransfer(&g_EDMA_Handle);

		FTM_StartClock(0);
		is_init = true;
	}
}

void md_writeBuffer(pixel_t *new_buffer)
{
	uint16_t i = 0;
	uint16_t * backBuffer = (currBuffer == buffers[0]) ? buffers[1]:buffers[0];

	while(!transfer_done)
	{

	}

	transfer_done = false;
	for (i = 0; i < PIXELS; i++)
	{
		backBuffer[i+PRE] = LOW_DUTY;
	}

	for (i = 0; i < DISPLAY_SIZE; i++)
	{
		pixel_buffer[i] = new_buffer[i];

		backBuffer[PRE + i * 24 +  7 - bright] = new_buffer[i].G ? ONE : ZERO;
		backBuffer[PRE + i * 24 + 15 - bright] = new_buffer[i].R ? ONE : ZERO;
		backBuffer[PRE + i * 24 + 23 - bright] = new_buffer[i].B ? ONE : ZERO;
	}
//	change_buffer = true;

	currBuffer = backBuffer;

	EDMA_PrepareTransfer(&g_transferConfig, (void *)(currBuffer), sizeof(uint16_t),
								(void *)FTM_GetCnVAddress(0, 0), sizeof(uint16_t),
								sizeof(uint16_t), (MATRIX_LEN) * sizeof(uint16_t) ,
								kEDMA_MemoryToPeripheral);

	EDMA_SetTransferConfig(DMA0, DMA_CHANEL, &g_transferConfig, NULL);
	EDMA_StartTransfer(&g_EDMA_Handle);

	FTM_StartClock(0);
	while(!FTM_IsInterruptPending (0,FTM_CH_0)){}; // Sync with CHF
	FTM_offOM(0,0);

}

pixel_t md_makeColor(bool r, bool g, bool b)
{

	pixel_t ret = {.R = r, .G = g, .B = b};
	return ret;
}

void md_setBrightness(uint8_t brigthness)
{
	uint8_t new_b = brigthness / 32;
	//if(new_b == 0){new_b = 1;}
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

	while(!FTM_IsInterruptPending (0,FTM_CH_0)){}; // Sync with CHF
	FTM_StopClock(0);
	//Systick_ResumeCallback(timer_id);
	FTM_onOM(0,0);

	transfer_done = true;
}

static void md_timerCallback(void)
{
	Systick_PauseCallback(timer_id);

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
							sizeof(uint16_t), (MATRIX_LEN) * sizeof(uint16_t) ,
							kEDMA_MemoryToPeripheral);

	EDMA_SetTransferConfig(DMA0, DMA_CHANEL, &g_transferConfig, NULL);
	EDMA_StartTransfer(&g_EDMA_Handle);
	//while(!FTM_IsInterruptPending (0,FTM_CH_0)){}; // Sync with CHF
	//FTM_SetCounter(0, FTM_CH_0, currBuffer[0]);
	FTM_StartClock(0);

	while(!FTM_IsInterruptPending (0,FTM_CH_0)){}; // Sync with CHF
	FTM_offOM(0,0);
}
