/***************************************************************************/ /**
  @file     matrix display.c
  @brief    8x8 RGB display source
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/


#include "dma.h"
#include "ftm.h"
#include "board.h"
#include "matrix_display.h"
#include "MK64F12.h"

#define PIXEL_SIZE 24

#define ZERO 10
#define ONE 20
#define PULSE 30 - 1

static uint16_t buffer_1[DISPLAY_SIZE * PIXEL_SIZE + 1];
static uint16_t buffer_2[DISPLAY_SIZE * PIXEL_SIZE + 1];
static pixel_t pixel_buffer[DISPLAY_SIZE];
static bool change_buffer = false;
static uint8_t bright = 2;
static bool on = true;

void md_dmaCallback(void);

void md_Init(void)
{
	buffer_1[0] = 2;
	buffer_2[0] = 2;
	for (int i = 1; i <= DISPLAY_SIZE * PIXEL_SIZE; i++)
	{
		buffer_1[i] = ZERO;
		buffer_2[i] = ZERO;
	}

	PWM_Init(0, FTM_CH_0, FTM_PSC_x2, 2, 1, 4, FTM_lAssertedHigh, PULSE, ZERO, FTM_DMA_ON);

	int16_t ret = -sizeof(buffer_1);
	DMA_Init(0, 20, (uint32_t)(buffer_1), FTM_GetCnVAddress(0, 0), 0x02, 0x0, DMA16_bits, DMA16_bits, 2,
			 sizeof(buffer_1) / sizeof(buffer_1[0]), ret, &md_dmaCallback);
}
void md_changeBackBuffer(void)
{
	if(!on && change_buffer)
	{
		for(int i = 1; i <= DISPLAY_SIZE*PIXEL_SIZE; i++)
		{
			buffer_1[i] = buffer_2[i];

		}
		change_buffer = false;
	}
}

void md_writeBuffer(pixel_t *new_buffer)
{
	uint16_t i = 0;
	for (int i = 1; i <= DISPLAY_SIZE * PIXEL_SIZE; i++)
	{
		buffer_1[i] = ZERO;
		buffer_2[i] = ZERO;
	}
	for (i = 0; i < DISPLAY_SIZE; i++)
	{
		pixel_buffer[i] = new_buffer[i];
		buffer_2[i * 24 + 8 - bright] = new_buffer[i].G ? ONE : ZERO;
		buffer_2[i * 24 + 16 - bright] = new_buffer[i].R ? ONE : ZERO;
		buffer_2[i * 24 + 24 - bright] = new_buffer[i].B ? ONE : ZERO;
	}
	change_buffer = true;
}

void md_dmaCallback(void)
{
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
