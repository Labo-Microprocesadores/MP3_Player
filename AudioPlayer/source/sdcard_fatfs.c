/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "inc/fsl_sd.h"
#include "fsl_debug_console.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk/fsl_sd_disk.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "sdmmc_config.h"
#include "fsl_sysmpu.h"


#include "AudioPlayer.h"
#include "fsl_debug_console.h"
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
/*!
 * @brief wait card insert function.
 */
static status_t sdcardWaitCardInsert(void);

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
char * canciones[SONGS] = {  "Una lady.wav", "Vida de Rico.wav",
						"Besame.wav", "Favorito.wav", "Tusa.wav", "Tutu.wav","Si me tomo una cerveza.wav",
						"Despeinada.wav", "Chica Ideal.wav", "Taki Taki.wav",
						"Hasta la Luna.wav", "Solo necesito.wav"};
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
		//curr = (curr+1)%SONGS;
		curr++;
		if(curr >= SONGS)
		{
			curr = 0;
		}
		printf("TRACK %d: %s", curr, canciones[curr]);

		f_open(&g_fileObject, _T(canciones[curr]), (FA_READ));
	}
}
/*!
 * @brief Main function
 */
int main(void)
{
    FRESULT error;
    //const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    SYSMPU_Enable(SYSMPU, false);
    Mm_Init();
    AudioPlayer_Init();

    PRINTF("\r\nFATFS example to demonstrate how to use FATFS with SD card.\r\n");

    PRINTF("\r\nPlease insert a card into board.\r\n");


    /*if (sdcardWaitCardInsert() != kStatus_Success)
    {
        return -1;
    }

    if (f_mount(&g_fileSystem, driverNumberBuffer, 1U))
    {
        PRINTF("Mount volume failed.\r\n");
        return -1;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("Change drive failed.\r\n");
        return -1;
    }
#endif
     */
    PRINTF("\r\n Open test.mp3 \r\n");
    error = f_open(&g_fileObject, _T(canciones[curr]), (FA_READ));
    printf("TRACK %d: %s", curr, canciones[curr]);
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("File exists.\r\n");
        }
        else
        {
            PRINTF("Open file failed.\r\n");
            return -1;
        }
    }

    fillBuffer();
	printf("%d \r\n", g_bufferRead[0]);

    AudioPlayer_LoadSongInfo(g_bufferRead, 44100);
    AudioPlayer_Play();
    fillBuffer();
    PRINTF("\r\n Read and send to dac \r\n");
    while (true)
    {
    	if(AudioPlayer_IsBackBufferFree())
    	{
    		AudioPlayer_UpdateBackBuffer(g_bufferRead);
    		fillBuffer();
    	}
    }

    if (f_close(&g_fileObject))
    {
        PRINTF("\r\nClose file failed.\r\n");
        return -1;
    }

    while (true)
    {
    }
}

static status_t sdcardWaitCardInsert(void)
{
    BOARD_SD_Config(&g_sd, sdCallback, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    /* SD host init function */
    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        PRINTF("\r\nSD host init fail\r\n");
        return kStatus_Fail;
    }

    while(!cardIn){}

    return kStatus_Success;
}
