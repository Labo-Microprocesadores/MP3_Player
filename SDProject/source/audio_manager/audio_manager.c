/***************************************************************************/ /**
  @file     audio_manager.c
  @brief    Audio manager, to wrap file related function and decoding stuff
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>

#include "file_system_manager.h"
#include "memory_manager.h"
#include "AudioPlayer.h"
#include "vumeterRefresh.h"
#include "decoder.h"

#include "fsl_common.h"
#include "queue.h"

/******************************************************************************
 * DEFINES
 ******************************************************************************/

#define BUFFER_SIZE (AUDIO_PLAYER_BUFF_SIZE)
/*******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************/
static Mp3File_t currFile;

static int maxFile = 0;

SDK_ALIGN(static uint16_t g_bufferRead[BUFFER_SIZE] , SD_BUFFER_ALIGN_SIZE);
SDK_ALIGN(static short decoder_buffer[2*BUFFER_SIZE], SD_BUFFER_ALIGN_SIZE);
static float effects_in[BUFFER_SIZE], effects_out[BUFFER_SIZE];


/******************************************************************************
 *
 ******************************************************************************/
void Audio_init(void)
{
	FileSystem_ScanFiles(); // Build file system tree
	currFile = FileSystem_GetFirstFile();
	maxFile = FileSystem_GetFilesCount();
}

void Audio_nextFile(void)
{
	currFile = FileSystem_GetNextFile(currFile);
}

void Audio_prevFile(void)
{
	currFile = FileSystem_GetPreviousFile(currFile);
}

void Audio_selectFile(void)
{
	decoder_MP3LoadFile(currFile.path);
	/* Primeros dos buffer constante, no hay sonido */
	memset(g_bufferRead, 0, sizeof(g_bufferRead));

	/* Podria buscar el sample rate y mandarlo */
	AudioPlayer_LoadSongInfo(g_bufferRead, 44100);

	Audio_updateBuffer();
}

char * Audio_getCurrentName(void)
{
	return FileSystem_GetFileName(currFile);
}

void Audio_updateBuffer(void)
{
	uint16_t sampleCount = 0;
	uint8_t channelCount = 1;

	AudioPlayer_UpdateBackBuffer(g_bufferRead);

	/* Clean buffers to rewrite */
	memset(g_bufferRead, 0, sizeof(g_bufferRead));
	memset(decoder_buffer, 0, sizeof(decoder_buffer));

	/* Fetch the new frame */
	decoder_return_t check = decoder_MP3DecodedFrame(decoder_buffer, 2*BUFFER_SIZE, &sampleCount);
	/* Get the amount of channels in the frame */
	decoder_MP3GetLastFrameChannelCount(&channelCount);

	/* Scale from int16 to float[-1;1] */
	float coef = 1.0/32768.0;
	for (uint32_t index = 0; index < BUFFER_SIZE; index++)
	{
		effects_in[index] = decoder_buffer[channelCount * index]*coef;
	}

	/* aca van los efectos */
	/* Scale to 12 bits, to fit in the DAC */
	for (uint32_t index = 0; index < fin; index++)
	{
		g_bufferRead[index] = (effects_in/*out*/[index]+1)*2048;
	}

	if (check == DECODER_END_OF_FILE)
	{
		/* Por las dudas completo la salida para tener 0V */
		for (uint32_t index = (sampleCount / channelCount); index < BUFFER_SIZE ; index++)
		{
			g_bufferRead[index] = 2048;
		}


		/* Agarro el siguiente archivo, ver si es mejor levantar un evento o hacerlo asi */
		/*if (currFile.index == maxFile)
		{
			currFile = FileSystem_GetFirstFile();
		}
		else
		{
			currFile = FileSystem_GetNextFile(currFile);
		}

		decoder_MP3LoadFile(currFile.path);*/

		emitEvent(NEXT_SONG_EV);

	}

	vumeterRefresh_fft(arr, 44100.0, 80, 10000);
}


void Audio_play(void)
{
	AudioPlayer_Play();
}

void Audio_pause(void)
{
	AudioPlayer_Pause();
}

void Audio_stop(void)
{
	decoder_MP3LoadFile(currFile.path);
	AudioPlayer_Pause();
}

char * Audio_getArtist(void)
{
	return decoder_getFileArtist();
}

char * Aduio_getAlbum(void)
{
	return decoder_getFileAlbum();
}

char * Audio_getYear(void)
{
	return (char *)decoder_getFileYear();
}


