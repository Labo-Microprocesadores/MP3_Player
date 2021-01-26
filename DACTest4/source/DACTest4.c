/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dac.h"
#include "fsl_edma.h"
//#include "fsl_pdb.h"
#include "fsl_dmamux.h"
#include "fsl_pit.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*
#define DEMO_PDB_BASEADDR           PDB0
#define DEMO_PDB_MODULUS_VALUE      0xFFFU
#define DEMO_PDB_DELAY_VALUE        0U
#define DEMO_PDB_DAC_CHANNEL        kPDB_DACTriggerChannel0
#define DEMO_PDB_DAC_INTERVAL_VALUE 0xFFFU
*/

#define DEMO_DAC_BASEADDR           DAC0
#define DEMO_DMAMUX_BASEADDR        DMAMUX
#define DEMO_DMA_CHANNEL            0U
//#define DEMO_DMA_DAC_SOURCE         45U
#define DEMO_DMA_BASEADDR           DMA0
#define DAC_DATA_REG_ADDR           0x400cc000U
#define DEMO_DMA_IRQ_ID             DMA0_IRQn
#define DEMO_DAC_USED_BUFFER_SIZE 32U

//Agrego definiciones de PIT:
#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT_LED_HANDLER   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn
// REEMPLAZO: #define DEMO_DMA_DAC_SOURCE         45U ----> POR:
#define PIT_DMASOURCE		kDmaRequestMux0AlwaysOn63
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)



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
//static void PDB_Configuration(void);
/*!
 * @brief Initialize the PIT.
 */
static void PIT_Configuration(void);
/*!
 * @brief Initialize the DAC.
 */
static void DAC_Configuration(void);
/*!
 * @brief Callback function for EDMA.
 */
static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);

static void all_init(void);
static void all_start(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
edma_handle_t g_EDMA_Handle;                             /* Edma handler */
edma_transfer_config_t g_transferConfig;                 /* Edma transfer config. */
volatile uint32_t g_index                          = 0U; /* Index of the g_dacDataArray array. */
uint16_t g_dacDataArray[DEMO_DAC_USED_BUFFER_SIZE] = {
    0U,    401U,  799U,  1188U, 1567U, 1930U, 2275U, 2598U, 2895U, 3165U, 3405U, 3611U, 3783U, 3918U, 4016U, 4075U,
    4095U, 4075U, 4016U, 3918U, 3783U, 3611U, 3405U, 3165U, 2895U, 2598U, 2275U, 1930U, 1567U, 1188U, 799U,  401U};

//para pit:
volatile bool pitIsrFlag = false;
unsigned freq = 1000; //Recibir la frec para sample rate


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("DAC CONTINUOUS PDB EDMA DEMO\r\n");

    /* Initialize DMAMUX. */
    DMAMUX_Configuration();
    /* Initialize EDMA. */
    EDMA_Configuration();
    /* Initialize the HW trigger source. */
    //PDB_Configuration();
    PIT_Configuration();
    /* Initialize DAC. */
    DAC_Configuration();

   // all_init();
   // all_start();

    /* Generate continuous trigger signal to DAC. */
   // PDB_DoSoftwareTrigger(DEMO_PDB_BASEADDR);
    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);

    PRINTF("Please probe the DAC output with a oscilloscope.\r\n");
    while (1)
    {
        if (true == pitIsrFlag)
        {
            PRINTF("\r\n Channel No.0 interrupt is occurred !");
            pitIsrFlag = false;
        }
    }
}


static void all_init()
{
	dac_config_t dacConfigStruct;
	dac_buffer_config_t dacBufferConfigStruct;
	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);

	 /* Configure the DAC buffer. */ // AGREGO ESTO
	DAC_EnableBuffer(DEMO_DAC_BASEADDR, true);
	DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
	dacBufferConfigStruct.triggerMode = kDAC_BufferTriggerByHardwareMode;
	DAC_SetBufferConfig(DEMO_DAC_BASEADDR, &dacBufferConfigStruct);
	DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U); /* Make sure the read pointer to the start. */
    DAC_EnableBufferInterrupts(DEMO_DAC_BASEADDR, kDAC_BufferReadPointerTopInterruptEnable);
    DAC_EnableBufferDMA(DEMO_DAC_BASEADDR, true);

	pit_config_t pitConfig;
	PIT_GetDefaultConfig(&pitConfig);
	pitConfig.enableRunInDebug=0;
	PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	DMAMUX_Init(DEMO_DMAMUX_BASEADDR);
	DMAMUX_DisableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);
	DMAMUX_SetSource(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL, PIT_DMASOURCE);//DEMO_DMA_DAC_SOURCE); /* Map ADC source to channel 0 */
	DMAMUX_EnablePeriodTrigger(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);

	edma_config_t userConfig;
	EDMA_GetDefaultConfig(&userConfig);
	userConfig.enableRoundRobinArbitration=true;
	userConfig.enableDebugMode = false;
	EDMA_Init(DEMO_DMA_BASEADDR, &userConfig);
	EDMA_CreateHandle(&g_EDMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
	EDMA_SetCallback(&g_EDMA_Handle, Edma_Callback, NULL);

	DAC_Enable(DEMO_DAC_BASEADDR, true);
}

static void all_start(void)
{
	PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(1000000U/freq, PIT_SOURCE_CLOCK)); //agrego /freq y +1
	EDMA_PrepareTransfer(&g_transferConfig, (void *)(g_dacDataArray + g_index), sizeof(uint16_t),
	                         (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
	                         DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);
	EDMA_SubmitTransfer(&g_EDMA_Handle, &g_transferConfig);

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);
    /* Enable at the NVIC */
    EnableIRQ(PIT_IRQ_ID);

    //    EDMA_EnableChannelInterrupts(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, kEDMA_MajorInterruptEnable);
    /* Enable transfer. */
    EDMA_StartTransfer(&g_EDMA_Handle);

    DMAMUX_EnableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);

}

static void PIT_Configuration(void)
{
    pit_config_t pitConfig;
    /*
         * pitConfig.enableRunInDebug = false;
         */
        PIT_GetDefaultConfig(&pitConfig);

        /* Init pit module */
        PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

        /* Set timer period for channel 0 */
        PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(1000000U/freq, PIT_SOURCE_CLOCK)+1); //agrego /freq y +1

        /* Enable timer interrupts for channel 0 */
        PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

        /* Enable at the NVIC */
        EnableIRQ(PIT_IRQ_ID);
}


static void EDMA_Configuration(void)
{
    edma_config_t userConfig;

    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DEMO_DMA_BASEADDR, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL);
    EDMA_SetCallback(&g_EDMA_Handle, Edma_Callback, NULL);
    EDMA_PrepareTransfer(&g_transferConfig, (void *)(g_dacDataArray + g_index), sizeof(uint16_t),
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
}

static void DMAMUX_Configuration(void)
{
    /* Configure DMAMUX */
    DMAMUX_Init(DEMO_DMAMUX_BASEADDR);
    DMAMUX_SetSource(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL, PIT_DMASOURCE);//DEMO_DMA_DAC_SOURCE); /* Map ADC source to channel 0 */
    DMAMUX_EnableChannel(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL); //VER SI DEJAR ESO O PONER DMAMUX_EnablePeriodTrigger(DEMO_DMAMUX_BASEADDR, DEMO_DMA_CHANNEL);
}

/* Enable the trigger source of PDB. */

//static void PDB_Configuration(void)
//{
//    pdb_config_t pdbConfigStruct;
//    pdb_dac_trigger_config_t pdbDacTriggerConfigStruct;
//
//    /*
//     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
//     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
//     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
//     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
//     * pdbConfigStruct.enableContinuousMode = true;
//     */
//    PDB_GetDefaultConfig(&pdbConfigStruct);
//    pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor40;
//    pdbConfigStruct.enableContinuousMode        = true;
//    PDB_Init(DEMO_PDB_BASEADDR, &pdbConfigStruct);
//    PDB_EnableInterrupts(DEMO_PDB_BASEADDR, kPDB_DelayInterruptEnable);
//    PDB_SetModulusValue(DEMO_PDB_BASEADDR, DEMO_PDB_MODULUS_VALUE);
//    PDB_SetCounterDelayValue(DEMO_PDB_BASEADDR, DEMO_PDB_DELAY_VALUE);
//
//    /* Set DAC trigger. */
//    pdbDacTriggerConfigStruct.enableExternalTriggerInput = false;
//    pdbDacTriggerConfigStruct.enableIntervalTrigger      = true;
//    PDB_SetDACTriggerConfig(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, &pdbDacTriggerConfigStruct);
//    PDB_SetDACTriggerIntervalValue(DEMO_PDB_BASEADDR, DEMO_PDB_DAC_CHANNEL, DEMO_PDB_DAC_INTERVAL_VALUE);
//
//    /* Load PDB values. */
//    PDB_DoLoadValues(DEMO_PDB_BASEADDR);
//}

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

    /* Enable DMA. */
    DAC_EnableBufferInterrupts(DEMO_DAC_BASEADDR, kDAC_BufferReadPointerTopInterruptEnable);
    DAC_EnableBufferDMA(DEMO_DAC_BASEADDR, true);
}



static void Edma_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    /* Clear Edma interrupt flag. */
    EDMA_ClearChannelStatusFlags(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, kEDMA_InterruptFlag);
    /* Setup transfer */
    g_index += DAC_DATL_COUNT;
    if (g_index == DEMO_DAC_USED_BUFFER_SIZE)
    {
        g_index = 0U;
    }
    EDMA_PrepareTransfer(&g_transferConfig, (void *)(g_dacDataArray + g_index), sizeof(uint16_t),
                         (void *)DAC_DATA_REG_ADDR, sizeof(uint16_t), DAC_DATL_COUNT * sizeof(uint16_t),
                         DAC_DATL_COUNT * sizeof(uint16_t), kEDMA_MemoryToMemory);
    EDMA_SetTransferConfig(DEMO_DMA_BASEADDR, DEMO_DMA_CHANNEL, &g_transferConfig, NULL);
    /* Enable transfer. */
    EDMA_StartTransfer(&g_EDMA_Handle);
}

void PIT_LED_HANDLER(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
    pitIsrFlag = true;
    /* Added for, and affects, all PIT handlers. For CPU clock which is much larger than the IP bus clock,
     * CPU can run out of the interrupt handler before the interrupt flag being cleared, resulting in the
     * CPU's entering the handler again and again. Adding DSB can prevent the issue from happening.
     */
    __DSB();
}
