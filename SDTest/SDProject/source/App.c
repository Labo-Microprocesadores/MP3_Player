/***************************************************************************/ /**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "fsl_common.h"
#include "memory_manager.h"
#include "LCD_GDM1602A.h"
#include "AudioPlayer.h"
#include "file_system_manager.h"
#include "ff.h"
#include "matrix_display.h"
#include "gpio.h"
#include "SysTick.h"
#include "vumeterRefresh.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BUFFER_SIZE (AUDIO_PLAYER_BUFF_SIZE)
const pixel_t blank = {false, false, false};
const pixel_t on = {true, true, true};
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static FIL g_fileObject;
static Mp3File_t currFile;
static int maxFile = 0;
static bool start = false;

SDK_ALIGN(static uint16_t g_bufferRead[BUFFER_SIZE], SD_BUFFER_ALIGN_SIZE);
SDK_ALIGN(static uint8_t g_bufferRead2[BUFFER_SIZE * 2], SD_BUFFER_ALIGN_SIZE);

//static pixel_t m_pixel_buffer[DISPLAY_SIZE];
void fillBuffer(void);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/
void update(void)
{
	static uint8_t counter = 0;
	static bool state = false;
	counter++;
	if(counter == (state?5:30))
	{
		if(!state)
		{
			AudioPlayer_Pause();
		}
		else
		{
			AudioPlayer_Play();
		}
		state = !state;
		counter = 0;
	}
}
/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
	SysTick_Init();
	//SysTick_AddCallback(update, 1000 /*, false*/);
	Mm_Init();
	LCD_Init();

	maxFile = FileSystem_GetFilesCount();
	if (maxFile != 0)
	{
		currFile = FileSystem_GetFirstFile();
		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_close(&g_fileObject);
	}
	md_Init();

	AudioPlayer_Init();
	vumeterRefresh_init();
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
	if (!start)
	{
		if (LCD_isInit())
		{
			start = true;
			f_open(&g_fileObject, _T(currFile.path), (FA_READ));
			fillBuffer();

			char track[] = "TRACK __";
			track[6] = currFile.index / 10 + '0';
			track[7] = currFile.index % 10 + '0';
			LCD_writeStrInPos(track, 8, 0, 0);
			LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);

			AudioPlayer_LoadSongInfo(g_bufferRead, 44100);
			AudioPlayer_Play();
			fillBuffer();
		}
		return;
	}

	if (AudioPlayer_IsBackBufferFree())
	{
		AudioPlayer_UpdateBackBuffer(g_bufferRead);
		/* Prepare buffer for next time */
		fillBuffer();
	}
}

void fillBuffer(void)
{
	FRESULT error;
	UINT bytesRead;
	float arr[1024];

	memset(g_bufferRead2, 0, sizeof(g_bufferRead2));
	memset(g_bufferRead, 0, sizeof(g_bufferRead));

	error = f_read(&g_fileObject, g_bufferRead2, sizeof(g_bufferRead2), &bytesRead);
	for (uint16_t i = 0; i < bytesRead / 2; i++)
	{
		g_bufferRead[i] = ((uint16_t)g_bufferRead2[2 * i] << 8) | (g_bufferRead2[2 * i + 1]);
	}
	if ((error) || (bytesRead != sizeof(g_bufferRead)))
	{
		for (uint16_t i = (bytesRead / sizeof(uint16_t)); i < 1024U; i++)
		{
			g_bufferRead[i] = 1024U;
		}

		f_close(&g_fileObject);
		if (currFile.index == maxFile)
		{
			currFile = FileSystem_GetFirstFile();
		}
		else
		{
			currFile = FileSystem_GetNextFile(currFile);
		}

		char track[] = "TRACK __";
		track[6] = currFile.index / 10 + '0';
		track[7] = currFile.index % 10 + '0';
		LCD_writeStrInPos(track, 8, 0, 0);
		LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);
		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_open(&g_fileObject, _T(currFile.path), (FA_READ));
	}
	//update();
	for (uint16_t i = 0; i < 1024; i++)
	{
		arr[i] = 1.0 * g_bufferRead[i];
	}
	vumeterRefresh_fft(arr, 44100.0, 80, 10000);
}
