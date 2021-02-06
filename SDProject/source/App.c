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

#include "gpio.h"
#include "SysTick.h"

#include "memory_manager.h"
#include "file_system_manager.h"
#include "ff.h"

#include "LCD_GDM1602A.h"
#include "matrix_display.h"
#include "AudioPlayer.h"
#include "vumeterRefresh.h"
#include "decoder.h"
#include "board.h"
#include "button.h"
#include "power_mode_switch.h"

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
static bool playing = false;

SDK_ALIGN(static uint16_t g_bufferRead[BUFFER_SIZE], SD_BUFFER_ALIGN_SIZE);
static float effects_in[BUFFER_SIZE], effects_out[BUFFER_SIZE];
short decoder_buffer[2*BUFFER_SIZE];

//static pixel_t m_pixel_buffer[DISPLAY_SIZE];
void fillBuffer(void);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/
void getEvents(void)
{
	if(wasTap(PIN_SW_A))
	{
		if(playing)
			AudioPlayer_Pause();
		else
			AudioPlayer_Play();
		playing = !playing;
	}

	if(wasTap(PIN_SW_B))
	{
		f_close(&g_fileObject);

		currFile = FileSystem_GetPreviousFile(currFile);

		char track[] = "TRACK __        ";
		track[6] = currFile.index / 10 + '0';
		track[7] = currFile.index % 10 + '0';
		LCD_writeStrInPos(track, 16, 0, 0);
		char path[50];

		uint8_t len = strlen(currFile.path)-1 ;
		uint8_t mod = len%DISPLAY_COLUMNS;
		if(mod == 0)
		{
			len+=DISPLAY_COLUMNS;
		}
		else
		{
			len += DISPLAY_COLUMNS-mod;
		}

		memset(path, 0x20, 50);
		memcpy(path, &currFile.path[1],  strlen(currFile.path) - 1);
		LCD_writeShiftingStr(path,  len, 1 , MIDIUM);

		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_open(&g_fileObject, _T(currFile.path), (FA_READ));
	}

	if(wasTap(PIN_SW_C))
	{
		f_close(&g_fileObject);

		currFile = FileSystem_GetNextFile(currFile);

		char track[] = "TRACK __        ";
		track[6] = currFile.index / 10 + '0';
		track[7] = currFile.index % 10 + '0';
		LCD_writeStrInPos(track, 16, 0, 0);

		char path[50];

		uint8_t len = strlen(currFile.path)-1 ;
		uint8_t mod = len%DISPLAY_COLUMNS;
		if(mod == 0)
		{
			len+=DISPLAY_COLUMNS;
		}
		else
		{
			len += DISPLAY_COLUMNS-mod;
		}

		memset(path, 0x20, 50);
		memcpy(path, &currFile.path[1],  strlen(currFile.path) - 1);
		LCD_writeShiftingStr(path,  len, 1 , MIDIUM);

		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_open(&g_fileObject, _T(currFile.path), (FA_READ));
	}
}
void aux(char * path)
{
	if(FileSystem_isMp3File(path))
		FileSystem_AddFile(path);
}
/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
	SysTick_Init();

	Mm_Init();//aux); //Memory manager
	LCD_Init();   //LCD Driver

	md_Init();	  //NeoPixel matrix

	decoder_MP3DecoderInit(); // Init decoder

	AudioPlayer_Init();	//Audio Player
	vumeterRefresh_init(); // FFT
	PowerMode_Init();

	buttonsInit();
	buttonConfiguration(PIN_SW_A, LKP, 20); //20*50=1seg
	buttonConfiguration(PIN_SW_B, LKP, 20);
	buttonConfiguration(PIN_SW_C, LKP, 20);
	buttonConfiguration(PIN_SW_D, LKP, 20);

	maxFile = FileSystem_GetFilesCount();
	if (maxFile != 0)
	{
		currFile = FileSystem_GetFirstFile();
		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		//f_close(&g_fileObject);
	}

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
	if (!start)
	{
		if (LCD_isInit())
		{
			start = true;
			//f_open(&g_fileObject, _T(currFile.path), (FA_READ));

			decoder_MP3LoadFile(currFile.path);

			printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
			char * fileName = decoder_getFileTitle();
			char * fileArtist = decoder_getFileArtist();
			char * fileAlbum = decoder_getFileAlbum();
			char * fileYear = (char *)decoder_getFileYear();
			char * trackNum = (char *)decoder_getFileTrackNum();
			printf("Name: %s.\nArtist: %s.\nAlbum: %s.\nYear: %s.\nTrackNum: %s.\n", fileName, fileArtist, fileAlbum, fileYear, trackNum);
			fillBuffer();

			char track[] = "TRACK __        ";
			track[6] = currFile.index / 10 + '0';
			track[7] = currFile.index % 10 + '0';
			LCD_writeStrInPos(track, 16, 0, 0);

			char path[50];

			uint8_t len = strlen(currFile.path)-1 ;
			uint8_t mod = len%DISPLAY_COLUMNS;
			if(mod == 0)
				len+=DISPLAY_COLUMNS;
			else
				len += DISPLAY_COLUMNS-mod;

			memset(path, 0x20, 50);
			memcpy(path, &currFile.path[1],  strlen(currFile.path) - 1);
			LCD_writeShiftingStr(path,  len, 1 , MIDIUM);

			AudioPlayer_LoadSongInfo(g_bufferRead, 44100);
			AudioPlayer_Play();
			playing = true;
			fillBuffer();
		}
		return;
	}
	else
	{
		if (AudioPlayer_IsBackBufferFree())
		{
			AudioPlayer_UpdateBackBuffer(g_bufferRead);
			/* Prepare buffer for next time */
			fillBuffer();
		}
		getEvents();
	}
}
#ifndef NO_DECODER
void fillBuffer(void)
{
	uint16_t sampleCount = 0;
	uint8_t channelCount = 1;

	memset(g_bufferRead, 0, sizeof(g_bufferRead));
	memset(decoder_buffer, 0, sizeof(decoder_buffer));

	decoder_return_t check = decoder_MP3DecodedFrame(decoder_buffer, BUFFER_SIZE, &sampleCount);

	decoder_MP3GetLastFrameChannelCount(&channelCount);

	uint16_t fin = (sampleCount / channelCount);
	if(fin > BUFFER_SIZE)
	{
		fin = BUFFER_SIZE;
		printf("ERROR BUFFER LARGER !!!!!!!!!!!!!!!!");
	}

	float coef = 1.0/32768.0;
	for (uint32_t index = 0; index < fin; index++)
	{
		effects_in[index] = decoder_buffer[channelCount * index]*coef;
	}

	for (uint32_t index = 0; index < fin; index++)
	{
		g_bufferRead[index] = (effects_out[index]+1)*2048;
	}

	if (check == DECODER_END_OF_FILE)
	{
		for (uint32_t index = (sampleCount / channelCount); index < BUFFER_SIZE ; index++)
		{
			g_bufferRead[index] = 2048;
		}

		if (currFile.index == maxFile)
		{
			currFile = FileSystem_GetFirstFile();
		}
		else
		{
			currFile = FileSystem_GetNextFile(currFile);
		}

		char track[] = "TRACK __        ";
		track[6] = currFile.index / 10 + '0';
		track[7] = currFile.index % 10 + '0';
		LCD_writeStrInPos(track, 16, 0, 0);

		char path[50];

		uint8_t len = strlen(currFile.path)-1 ;
		uint8_t mod = len%DISPLAY_COLUMNS;
		if(mod == 0)
			len+=DISPLAY_COLUMNS;
		else
			len += DISPLAY_COLUMNS-mod;

		memset(path, 0x20, 50);
		memcpy(path, &currFile.path[1],  strlen(currFile.path) - 1);
		LCD_writeShiftingStr(path,  len, 1 , MIDIUM);

		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
//		f_open(&g_fileObject, _T(currFile.path), (FA_READ));

		decoder_MP3LoadFile(currFile.path);

	}

	//vumeterRefresh_fft(arr, 44100.0, 80, 10000);
}
#else
void fillBuffer_read(void)
{
	FRESULT error;
	UINT bytesRead;
	float arr[FFT_SIZE];

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
			g_bufferRead[i] = 2048U;
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

		char track[] = "TRACK __        ";
		track[6] = currFile.index / 10 + '0';
		track[7] = currFile.index % 10 + '0';
		LCD_writeStrInPos(track, 16, 0, 0);

		char path[50];

		uint8_t len = strlen(currFile.path)-1 ;
		uint8_t mod = len%DISPLAY_COLUMNS;
		if(mod == 0)
			len+=DISPLAY_COLUMNS;
		else
			len += DISPLAY_COLUMNS-mod;

		memset(path, 0x20, 50);
		memcpy(path, &currFile.path[1],  strlen(currFile.path) - 1);
		LCD_writeShiftingStr(path,  len, 1 , MIDIUM);

		printf("TRACK %d: %s\r\n", currFile.index, currFile.path);
		f_open(&g_fileObject, _T(currFile.path), (FA_READ));
	}
	//update();
	for (uint16_t i = 0; i < FFT_SIZE; i++)
	{
		arr[i] = 1.0 * g_bufferRead[i];
	}
	vumeterRefresh_fft(arr, 44100.0, 80, 10000);
}
#endif
