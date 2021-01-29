/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdmmc_host.h"
#include "inc/fsl_sdmmc_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SDMMCHOST_TRANSFER_COMPLETE_TIMEOUT (~0U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief SDMMCHOST detect card insert status by host controller.
 * @param base host base address.
 * @param userData user can register a application card insert callback through userData.
 */
static void SDMMCHOST_DetectCardInsertByHost(SDHC_Type *base, void *userData);

/*!
 * @brief SDMMCHOST detect card remove status by host controller.
 * @param base host base address.
 * @param userData user can register a application card insert callback through userData.
 */
static void SDMMCHOST_DetectCardRemoveByHost(SDHC_Type *base, void *userData);

/*!
 * @brief SDMMCHOST transfer complete callback.
 * @param base host base address.
 * @param handle host handle.
 * @param status interrupt status.
 * @param userData user data.
 */
static void SDMMCHOST_TransferCompleteCallback(SDHC_Type *base, sdhc_handle_t *handle, status_t status, void *userData);

/*!
 * @brief SDMMCHOST error recovery.
 * @param base host base address.
 */
static void SDMMCHOST_ErrorRecovery(SDHC_Type *base);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SDMMCHOST_DetectCardInsertByHost(SDHC_Type *base, void *userData)
{
    sd_detect_card_t *cd = NULL;

    /* disable card insert insterrupt */
    SDHC_DisableInterruptSignal(base, kSDHC_CardInsertionFlag);

    if (userData != NULL)
    {
        cd = (sd_detect_card_t *)(((sdmmchost_t *)userData)->cd);
        if (cd != NULL)
        {
            if (cd->callback != NULL)
            {
                cd->callback(true, cd->userData);
            }

            if (cd->dat3PullFunc != NULL)
            {
                cd->dat3PullFunc(kSD_DAT3PullUp);
            }
        }
    }
}

static void SDMMCHOST_DetectCardRemoveByHost(SDHC_Type *base, void *userData)
{
    sd_detect_card_t *cd = NULL;

    SDHC_DisableInterruptSignal(base, kSDHC_CardRemovalFlag);

    if (userData != NULL)
    {
        cd = (sd_detect_card_t *)(((sdmmchost_t *)userData)->cd);
        if (cd != NULL)
        {
            if (cd->callback != NULL)
            {
                cd->callback(false, cd->userData);
            }
        }
    }
}

static void SDMMCHOST_CardInterrupt(SDHC_Type *base, void *userData)
{
    sdio_card_int_t *cardInt = NULL;

    /* application callback */
    if (userData != NULL)
    {
        cardInt = ((sdmmchost_t *)userData)->cardInt;
        if ((cardInt != NULL) && (cardInt->cardInterrupt != NULL))
        {
            cardInt->cardInterrupt(cardInt->userData);
        }
    }
}

status_t SDMMCHOST_CardIntInit(sdmmchost_t *host, void *sdioInt)
{
    host->cardInt                       = sdioInt;
    host->handle.callback.SdioInterrupt = SDMMCHOST_CardInterrupt;
    SDMMCHOST_EnableCardInt(host, true);

    return kStatus_Success;
}

status_t SDMMCHOST_CardDetectInit(sdmmchost_t *host, void *cd)
{
    SDHC_Type *base        = host->hostController.base;
    sd_detect_card_t *sdCD = (sd_detect_card_t *)cd;
    if ((cd == NULL) || (sdCD->type != kSD_DetectCardByHostDATA3))
    {
        return kStatus_Fail;
    }

    host->cd = cd;

    /* enable card detect through DATA3 */
    SDHC_CardDetectByData3(base, true);
    /* enable card detect interrupt */
    SDHC_EnableInterruptStatus(base, kSDHC_CardRemovalFlag);
    SDHC_ClearInterruptStatusFlags(base, (uint32_t)kSDHC_CardInsertionFlag | (uint32_t)kSDHC_CardRemovalFlag);

    if (SDMMCHOST_CardDetectStatus(host) == (uint32_t)kSD_Inserted)
    {
        if (sdCD->callback != NULL)
        {
            sdCD->callback(true, sdCD->userData);
        }
    }
    else
    {
        SDHC_EnableInterruptStatus(base, kSDHC_CardInsertionFlag);
        SDHC_EnableInterruptSignal(base, kSDHC_CardInsertionFlag);
    }

    return kStatus_Success;
}

uint32_t SDMMCHOST_CardDetectStatus(sdmmchost_t *host)
{
    sd_detect_card_t *sdCD = (sd_detect_card_t *)(host->cd);
    uint32_t insertStatus  = kSD_Removed;

    if (sdCD->dat3PullFunc != NULL)
    {
        sdCD->dat3PullFunc(kSD_DAT3PullDown);
    }

    if ((SDHC_GetPresentStatusFlags(host->hostController.base) & (uint32_t)kSDHC_CardInsertedFlag) != 0U)
    {
        insertStatus = kSD_Inserted;
        if (sdCD->dat3PullFunc != NULL)
        {
            sdCD->dat3PullFunc(kSD_DAT3PullUp);
        }
    }

    return insertStatus;
}

status_t SDMMCHOST_PollingCardDetectStatus(sdmmchost_t *host, uint32_t waitCardStatus, uint32_t timeout)
{
    assert(host != NULL);
    assert(host->cd != NULL);

    uint32_t event       = 0U;

    if(true)
    {
        return kStatus_Success;
    }

    /* Wait card inserted. */
    do
    {
        if(true)
    	{
            return kStatus_Fail;
        }
        else
        {
        	break;
	    }
    } while (true);

    return kStatus_Success;
}

status_t SDMMCHOST_WaitCardDetectStatus(SDMMCHOST_TYPE *hostBase,
                                        const sdmmchost_detect_card_t *cd,
                                        bool waitCardStatus)
{
    assert(cd != NULL);

    while (((SDHC_GetInterruptStatusFlags(hostBase) & (uint32_t)kSDHC_CardInsertionFlag) != 0U) != waitCardStatus)
    {
    }

    return kStatus_Success;
}

static void SDMMCHOST_TransferCompleteCallback(SDHC_Type *base, sdhc_handle_t *handle, status_t status, void *userData)
{
	/* Not used and errased */
	return;
}

status_t SDMMCHOST_TransferFunction(sdmmchost_t *host, sdmmchost_transfer_t *content)
{
    status_t error = kStatus_Success;
    do
    {
        error = SDHC_TransferBlocking(host->hostController.base, host->dmaDesBuffer, host->dmaDesBufferWordsNum,content );
    } while (error == kStatus_SDHC_BusyTransferring);

    if (error != kStatus_Success)
    {
        error = kStatus_Fail;
        /* host error recovery */
        SDMMCHOST_ErrorRecovery(host->hostController.base);
    }

    return error;
}

static void SDMMCHOST_ErrorRecovery(SDHC_Type *base)
{
    uint32_t status = 0U;
    /* get host present status */
    status = SDHC_GetPresentStatusFlags(base);
    /* check command inhibit status flag */
    if ((status & (uint32_t)kSDHC_CommandInhibitFlag) != 0U)
    {
        /* reset command line */
        (void)SDHC_Reset(base, kSDHC_ResetCommand, 100U);
    }
    /* check data inhibit status flag */
    if ((status & (uint32_t)kSDHC_DataInhibitFlag) != 0U)
    {
        /* reset data line */
        (void)SDHC_Reset(base, kSDHC_ResetData, 100U);
    }
}

void SDMMCHOST_SetCardPower(sdmmchost_t *host, bool enable)
{
    /* host not support */
}

void SDMMCHOST_PowerOffCard(SDMMCHOST_TYPE *base, const sdmmchost_pwr_card_t *pwr)
{
    if (pwr != NULL)
    {
        pwr->powerOff();
        SDK_DelayAtLeastUs(pwr->powerOffDelay_ms * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}

void SDMMCHOST_PowerOnCard(SDMMCHOST_TYPE *base, const sdmmchost_pwr_card_t *pwr)
{
    /* use user define the power on function  */
    if (pwr != NULL)
    {
        pwr->powerOn();
        SDK_DelayAtLeastUs(pwr->powerOnDelay_ms * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        /* Delay several milliseconds to make card stable. */
        SDK_DelayAtLeastUs(1000U * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
}

status_t SDMMCHOST_Init(sdmmchost_t *host)
{
    assert(host != NULL);

    sdhc_transfer_callback_t sdhcCallback = {0};
    sdhc_host_t *sdhcHost                 = &(host->hostController);

    /* Initializes SDHC. */
    sdhcHost->config.endianMode          = kSDHC_EndianModeLittle;
    sdhcHost->config.dmaMode             = kSDHC_DmaModeAdma2;
    sdhcHost->config.readWatermarkLevel  = 0x80U;
    sdhcHost->config.writeWatermarkLevel = 0x80U;
    SDHC_Init(sdhcHost->base, &(sdhcHost->config));

    /* Create handle for SDHC driver */
    sdhcCallback.TransferComplete = SDMMCHOST_TransferCompleteCallback;
    sdhcCallback.CardInserted     = SDMMCHOST_DetectCardInsertByHost;
    sdhcCallback.CardRemoved      = SDMMCHOST_DetectCardRemoveByHost;
    SDHC_TransferCreateHandle(sdhcHost->base, &host->handle, &sdhcCallback, host);

    return kStatus_Success;
}

void SDMMCHOST_Reset(sdmmchost_t *host)
{
    /* reserved for future */
}

void SDMMCHOST_SetCardBusWidth(sdmmchost_t *host, uint32_t dataBusWidth)
{
    SDHC_SetDataBusWidth(host->hostController.base, dataBusWidth == (uint32_t)kSDMMC_BusWdith1Bit ?
                                                        kSDHC_DataBusWidth1Bit :
                                                        dataBusWidth == (uint32_t)kSDMMC_BusWdith4Bit ?
                                                        kSDHC_DataBusWidth4Bit :
                                                        kSDHC_DataBusWidth8Bit);
}

void SDMMCHOST_Deinit(sdmmchost_t *host)
{
    sdhc_host_t *sdhcHost = &host->hostController;
    SDHC_Deinit(sdhcHost->base);
}

status_t SDMMCHOST_StartBoot(sdmmchost_t *host,
                             sdmmchost_boot_config_t *hostConfig,
                             sdmmchost_cmd_t *cmd,
                             uint8_t *buffer)
{
    /* not support */
    return kStatus_Success;
}

status_t SDMMCHOST_ReadBootData(sdmmchost_t *host, sdmmchost_boot_config_t *hostConfig, uint8_t *buffer)
{
    /* not support */
    return kStatus_Success;
}
