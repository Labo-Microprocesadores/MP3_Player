/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "AudioPlayer.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dac.h"
#include "fsl_edma.h"
#include "fsl_pdb.h"
#include "fsl_dmamux.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDB_BASEADDR           PDB0
#define DEMO_PDB_MODULUS_VALUE      0xFFFU
#define DEMO_PDB_DELAY_VALUE        0U
#define DEMO_PDB_DAC_CHANNEL        kPDB_DACTriggerChannel0
#define DEMO_PDB_DAC_INTERVAL_VALUE 0xFFFU
#define DEMO_DAC_BASEADDR           DAC0
#define DEMO_DMAMUX_BASEADDR        DMAMUX
#define DEMO_DMA_CHANNEL            0U
#define DEMO_DMA_DAC_SOURCE         45U
#define DEMO_DMA_BASEADDR           DMA0
#define DAC_DATA_REG_ADDR           0x400cc000U
#define DEMO_DMA_IRQ_ID             DMA0_IRQn


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the EDMA.
 */
static void EDMA_Configuration(void);
/*!
 * @brief Initialize the DMAMUX.
 */
static void DMAMUX_Configuration(void);
/*!
 * @brief Initialize the PDB.
 */
static void PDB_Configuration(void);
/*!
 * @brief Initialize the DAC.
 */
static void DAC_Configuration(void);
/*!
 * @brief Callback function for EDMA.
 */
static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);
/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;                             /* Edma handler */
edma_transfer_config_t g_transferConfig;                 /* Edma transfer config. */
volatile uint32_t g_index                          = 0U; /* Index of the g_dacDataArray array. */


/*
uint16_t buffers[2][AUDIO_PLAYER_BUFF_SIZE];
uint16_t * activeBuffer = buffers[0];
uint16_t * backBuffer= buffers[1];
*/
int16_t buffers[2][AUDIO_PLAYER_BUFF_SIZE];
int16_t * activeBuffer = buffers[0];
int16_t * backBuffer= buffers[1];
bool backBufferFree = false;


/*******************************************************************************
 * Code
 ******************************************************************************/
void AudioPlayer_DEMOMode(void)
{
	AudioPlayer_UpdateSampleRate(44100);
}

void AudioPlayer_Init(void)
{
	/* Initialize DMAMUX. */
	DMAMUX_Configuration();
	/* Initialize EDMA. */
	EDMA_Configuration();
	/* Initialize the HW trigger source. */
	// Lo de PDB se hace directamente en update sample rate porque esta relacionado.
	PDB_Configuration();
	/* Initialize DAC. */
	DAC_Configuration();
}

void AudioPlayer_LoadSongInfo(uint16_t * firstSongFrame, uint16_t sampleRate)
{
	memcpy(activeBuffer, firstSongFrame, AUDIO_PLAYER_BUFF_SIZE * sizeof(uint16_t));
	//activeBuffer = firstSongFrame;
	//backBuffer = secondSongFrame;
	backBufferFree = true;
	g_index = 0U;

	AudioPlayer_UpdateSampleRate(sampleRate);
}

//TODO: Hay que ver si hacer el PDB_Deinit antes de cada update sample rate, porque en definitiva cambia toda su config.
// Y para eso hay que chequear que a lo que usa PDB para triggerear no le afecte esto....
void AudioPlayer_UpdateSampleRate(uint16_t sampleRate) //PDB_Configuration
{
    pdb_config_t pdbConfigStruct;
    pdb_dac_trigger_config_t pdbDacTriggerConfigStruct;
    PDB_GetDefaultConfig(&pdbConfigStruct);

	if(sampleRate == 8000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider4;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 1875);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 1875);
	}
	else if(sampleRate == 11025)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider2;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 2721);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 2721);
	}
	else if(sampleRate == 12000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 125);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 125);
	}
	else if(sampleRate == 16000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor10;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 375);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 375);
	}
	else if(sampleRate == 22050)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 2721);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 2721);
	}
	else if(sampleRate == 24000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor20;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 125);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 125);
	}
	else if(sampleRate == 32000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 1875);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 1875);
	}
	else if(sampleRate == 44100)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider2;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 17);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 17);
	}
	else if(sampleRate == 48000)
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor10;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, 125);
		PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 125);
	}
	else //For testing with DEMO
	{
		pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
		pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
		PDB_SetModulusValue(DEMO_PDB_BASEADDR, DEMO_PDB_MODULUS_VALUE);
	}
	// Pongo estas configuraciones de PDB aca porque necesitan info del sample rate
	//pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
	//pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
	pdbConfigStruct.enableContinuousMode        = true;
	PDB_Init(DEMO_PDB_BASEADDR, &pdbConfigStruct);
	PDB_EnableInterrupts(DEMO_PDB_BASEADDR, kPDB_DelayInterruptEnable);
	//PDB_SetModulusValue(DEMO_PDB_BASEADDR, DEMO_PDB_MODULUS_VALUE);
	PDB_SetCounterDelayValue(DEMO_PDB_BASEADDR, DEMO_PDB_DELAY_VALUE);

    /* Set DAC trigger. */
    pdbDacTriggerConfigStruct.enableExternalTriggerInput = false;
    pdbDacTriggerConfigStruct.enableIntervalTrigger      = true;
    PDB_SetDACTriggerConfig(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, &pdbDacTriggerConfigStruct);
  //  PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, 17);//DEMO_PDB_DAC_INTERVAL_VALUE);

    /* Load PDB values. */
    PDB_DoLoadValues(DEMO_PDB_BASEADDR);
}

audioPlayerError AudioPlayer_UpdateBackBuffer(uint16_t * newBackBuffer)
{
	if(backBufferFree)
	{
		memcpy( backBuffer, newBackBuffer, AUDIO_PLAYER_BUFF_SIZE * sizeof(uint16_t));
		//backBuffer = newBackBuffer;
		backBufferFree = false;
		return AP_NO_ERROR;
	}
	else
		return AP_ERROR_BB_NOT_FREE;
}

bool AudioPlayer_IsBackBufferFree(void)
{
	return backBufferFree;
}

void AudioPlayer_Play(void)
{
	g_index = 0U;
	// DMAMUX:
    DMAMUX_EnableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);

	// EDMA:
	 EDMA_PrepareTransfer(&g_transferConfig, (void *)(activeBuffer + g_index), sizeof(uint16_t),
	                         (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
	                         DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);
	 EDMA_SubmitTransfer(&g_EDMA_Handle, &g_transferConfig);
	 /* Enable interrupt when transfer is done. */
	 EDMA_EnableChannelInterrupts(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, kEDMA_MajorInterruptEnable);
	#if defined(FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT) && FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT
	 /* Enable async DMA request. */
	 EDMA_EnableAsyncRequest(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, true);
	#endif /* FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT */
	/* Enable transfer. */
	EDMA_StartTransfer(&g_EDMA_Handle);

	// PDB:

	// DAC:
	/* Enable DMA. */
	DAC_EnableBufferInterrupts(DEMO_DAC_BASEADDR, kDAC_BufferReadPointerTopInterruptEnable);
	DAC_EnableBufferDMA(DEMO_DAC_BASEADDR, true);




	PDB_DoSoftwareTrigger(DEMO_PDB_BASEADDR);
}

void AudioPlayer_Pause(void)
{
	// DMAMUX:
	DMAMUX_DisableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);

	// PDB:
	PDB_DisableInterrupts(DEMO_PDB_BASEADDR, kPDB_DelayInterruptEnable);
}

void AudioPlayer_Stop(void)
{
	// DMAMUX:
	DMAMUX_DisableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);

	// PDB:
	PDB_DisableInterrupts(DEMO_PDB_BASEADDR, kPDB_DelayInterruptEnable);

	g_index = 0U;
	//currentSongFrame = firstSongFrame;
}

static void EDMA_Configuration(void)
{
    edma_config_t userConfig;

    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DEMO_DMA_BASEADDR, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    EDMA_SetCallback(&g_EDMA_Handle, Edma_Callback, NULL);
}

static void DMAMUX_Configuration(void)
{
    /* Configure DMAMUX */
    DMAMUX_Init(DEMO_DMAMUX_BASEADDR);
    DMAMUX_SetSource(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL, DEMO_DMA_DAC_SOURCE); /* Map ADC source to channel 0 */
}

/* Enable the trigger source of PDB. */
static void PDB_Configuration(void)
{
    pdb_config_t pdbConfigStruct;
    pdb_dac_trigger_config_t pdbDacTriggerConfigStruct;

    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = true;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);
    // Paso esto a load song info para cambiar los valores para el PDB
    pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
    pdbConfigStruct.enableContinuousMode        = true;
    PDB_Init(DEMO_PDB_BASEADDR, &pdbConfigStruct);
    PDB_EnableInterrupts(DEMO_PDB_BASEADDR, kPDB_DelayInterruptEnable);
    PDB_SetModulusValue(DEMO_PDB_BASEADDR, DEMO_PDB_MODULUS_VALUE);
    PDB_SetCounterDelayValue(DEMO_PDB_BASEADDR, DEMO_PDB_DELAY_VALUE);


    /* Set DAC trigger. */
    pdbDacTriggerConfigStruct.enableExternalTriggerInput = false;
    pdbDacTriggerConfigStruct.enableIntervalTrigger      = true;
    PDB_SetDACTriggerConfig(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, &pdbDacTriggerConfigStruct);
    PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, DEMO_PDB_DAC_INTERVAL_VALUE);

    /* Load PDB values. */
    PDB_DoLoadValues(DEMO_PDB_BASEADDR);
}

static void DAC_Configuration(void)
{
    dac_config_t dacConfigStruct;
    dac_buffer_config_t dacBufferConfigStruct;

    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASEADDR, true); /* Enable output. */

    /* Configure the DAC buffer. */
    DAC_EnableBuffer(DEMO_DAC_BASEADDR, true);
    DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
    dacBufferConfigStruct.triggerMode = kDAC_BufferTriggerByHardwareMode;
    DAC_SetBufferConfig(DEMO_DAC_BASEADDR, &dacBufferConfigStruct);
    DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U); /* Make sure the read pointer to the start. */
}

static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    /* Clear Edma interrupt flag. */
    EDMA_ClearChannelStatusFlags(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, kEDMA_InterruptFlag);
    /* Setup transfer */

    /*
    g_index += DAC_DATL_COUNT;
    if (g_index == DEMO_DAC_USED_BUFFER_SIZE)
    {
        g_index = 0U;
        if(used_buffer == 1)
        {
        	used_buffer = 2;
        }
        else if(used_buffer == 2)
        {
        	used_buffer = 1;
        }
    }

    if(used_buffer == 1)
    {
        EDMA_PrepareTransfer(&g_transferConfig, (void *)(g_dacDataArray + g_index), sizeof(uint16_t),
                             (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
                             DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);
    }
    else if(used_buffer == 2)
    {
        EDMA_PrepareTransfer(&g_transferConfig, (void *)(g_dacDataArray2 + g_index), sizeof(uint16_t),
                             (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
                             DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);
    }
     */

    g_index += DAC_DATL_COUNT; //TODO: si esto queda aca, tiene que haber una primera transferencia antes.
    if (g_index == AUDIO_PLAYER_BUFF_SIZE)
    {
        g_index = 0U;
        void * temp = activeBuffer;
        activeBuffer = backBuffer;
        backBuffer = temp;
        backBufferFree = true;
    }
    EDMA_PrepareTransfer(&g_transferConfig, (void *)(activeBuffer + g_index), sizeof(uint16_t),
                        (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
                        DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);


    EDMA_SetTransferConfig(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, &g_transferConfig, NULL);
    /* Enable transfer. */
    EDMA_StartTransfer(&g_EDMA_Handle);
}
