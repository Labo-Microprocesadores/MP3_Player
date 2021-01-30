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

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BUFFER_SIZE (AUDIO_PLAYER_BUFF_SIZE)
const pixel_t blank = {0,0,0};
const pixel_t on = {1,1,1};
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static FIL g_fileObject;
static Mp3File_t currFile;
static int maxFile = 0;
static bool start = false;

SDK_ALIGN(uint16_t g_bufferRead[BUFFER_SIZE], SD_BUFFER_ALIGN_SIZE);
SDK_ALIGN(uint8_t g_bufferRead2[BUFFER_SIZE*2], SD_BUFFER_ALIGN_SIZE);

static pixel_t pixel_buffer[DISPLAY_SIZE];
void fillBuffer(void);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
	Mm_Init();
	LCD_Init();
	AudioPlayer_Init();
	maxFile = FileSystem_GetFilesCount();
	if(maxFile != 0)
	{
		currFile = FileSystem_GetFirstFile();
		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_close(&g_fileObject);
	}
	md_Init();
	md_setBrightness(0);
	for(int i = 0; i <  DISPLAY_SIZE;i++)
	{
		pixel_buffer[i] = blank;
	}

	md_writeBuffer(pixel_buffer);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
	if(!start)
	{
		if(LCD_isInit())
		{
			start = true;
			f_open(&g_fileObject, _T(currFile.path), (FA_READ));
			fillBuffer();

			char track[] = "TRACK __";
			track[6] = currFile.index/10 + '0';
			track[7] = currFile.index%10 + '0';
			LCD_writeStrInPos(track, 8, 0, 0);
			LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path)-1, 1, 0, MIDIUM);

			uint8_t counter = currFile.index+1;
			for(uint8_t j; j < 8; j++)
			{
				for(uint8_t k; k<8;k++)
				{
					pixel_buffer[8*j+k] = (counter & (1<<j))?blank:on;
				}
			}
			md_writeBuffer(pixel_buffer);
			AudioPlayer_LoadSongInfo(g_bufferRead, 44100);
			AudioPlayer_Play();
			fillBuffer();
		}
		return;
	}

	if(AudioPlayer_IsBackBufferFree())
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

	memset(g_bufferRead2, 0, sizeof(g_bufferRead2));
	memset(g_bufferRead, 0, sizeof(g_bufferRead));

	error = f_read(&g_fileObject, g_bufferRead2, sizeof(g_bufferRead2), &bytesRead);
	for(uint16_t i = 0; i < bytesRead/2; i++)
	{
		g_bufferRead[i] = ((uint16_t)g_bufferRead2[2*i]<<8)|(g_bufferRead2[2*i+1]);
	}
	if ((error) || (bytesRead != sizeof(g_bufferRead)))
	{
		for(uint16_t i = (bytesRead/sizeof(uint16_t)); i<1024U; i++)
		{
			g_bufferRead[i] = 1024U;
		}

		f_close(&g_fileObject);
		if(currFile.index == maxFile)
		{
			currFile = FileSystem_GetFirstFile();
		}
		else
		{
			currFile = FileSystem_GetNextFile(currFile);
		}

		char track[] = "TRACK __";
		track[6] = currFile.index/10 + '0';
		track[7] = currFile.index%10 + '0';
		LCD_writeStrInPos(track, 8, 0, 0);
		LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path)-1, 1, 0, MIDIUM);
		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_open(&g_fileObject, _T(currFile.path), (FA_READ));
		uint8_t counter = currFile.index+1;
		for(uint8_t j; j < 8; j++)
		{
			for(uint8_t k; k<8;k++)
			{
				pixel_buffer[8*j+k] = (counter & (1<<j))?blank:on;
			}
		}
		md_writeBuffer(pixel_buffer);
	}
}







