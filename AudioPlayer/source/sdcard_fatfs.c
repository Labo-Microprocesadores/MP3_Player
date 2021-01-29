/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>

#include "ff.h"

#include "pin_mux.h"
#include "sdmmc_config.h"

#include "AudioPlayer.h"

#include "math.h"

#include "memory_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* buffer size (in byte) for read/write operations */
#define BUFFER_SIZE (AUDIO_PLAYER_BUFF_SIZE)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/
//static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject;   /* File object */

/* @brief decription about the read/write buffer
 * The size of the read/write buffer should be a multiple of 512, since SDHC/SDXC card uses 512-byte fixed
 * block length and this driver example is enabled with a SDHC/SDXC card.If you are using a SDSC card, you
 * can define the block length by yourself if the card supports partial access.
 * The address of the read/write buffer should align to the specific DMA data buffer address align value if
 * DMA transfer is used, otherwise the buffer address is not important.
 * At the same time buffer address/size should be aligned to the cache line size if cache is supported.
 */
/*! @brief Data written to the card */
SDK_ALIGN(uint16_t g_bufferWrite[BUFFER_SIZE], BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
/*! @brief Data read from the card */
SDK_ALIGN(uint16_t g_bufferRead[BUFFER_SIZE], BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
SDK_ALIGN(uint8_t g_bufferRead2[BUFFER_SIZE*2], BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
#define SONGS 12
/* Request this files (no true .wav files!!!) to store in sd card */
char * canciones[SONGS] = {
							"Taki Taki.wav","Hasta la Luna.wav",
							"Solo necesito.wav","Una lady.wav", "Vida de Rico.wav","Besame.wav",
							"Favorito.wav", "Tusa.wav", "Tutu.wav","Si me tomo una cerveza.wav",
							"Despeinada.wav", "Chica Ideal.wav",
						  };
uint8_t curr = 0;

bool cardIn = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void sdCallback(bool isInserted, void *userData)
{
	cardIn = isInserted;
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
		curr++;
		if(curr >= SONGS)
		{
			curr = 0;
		}
		printf("TRACK %d: %s\r\n", curr, canciones[curr]);

		f_open(&g_fileObject, _T(canciones[curr]), (FA_READ));
	}
}
/*!
 * @brief Main function
 */
int main(void)
{
    FRESULT error;
    /* Board Initialization */
    BOARD_InitPins();
    BOARD_BootClockRUN();

    printf("\r\nAudio Player example, reading raw audio from sd card\r\n");

    printf("\r\nPlease insert a card into board.\r\n");

    /* Init Memory manger, using SD and FATFS */
    Mm_Init();
    /* Init Audio player using DAC, PDB and DMA */
    AudioPlayer_Init();

    printf("\r\nOpening first file from playlist\r\n");
    /* Opening first file from playlist */
    error = f_open(&g_fileObject, _T(canciones[curr]), (FA_READ));
    printf("TRACK %d: %s\r\n", curr, canciones[curr]);
    if (error)
    {
    	printf("Open file failed.\r\n");
		return -1;
    }

    fillBuffer();

    /* Load first frame of the song */
    AudioPlayer_LoadSongInfo(g_bufferRead, 44100);
    /* Start Playing */
    AudioPlayer_Play();
    /* Preparing next buffer */
    fillBuffer();
    printf("\r\n Read and send to dac \r\n");
    while (true)
    {
    	/*
    	 * If the Audio Player has a buffer to fill, then send send the buffer that
    	 * was previously filled
    	 */
    	if(AudioPlayer_IsBackBufferFree())
    	{
    		AudioPlayer_UpdateBackBuffer(g_bufferRead);
    		/* Prepare buffer for next time */
    		fillBuffer();
    	}
    }
}
