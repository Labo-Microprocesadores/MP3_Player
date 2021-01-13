/***************************************************************************/ /**
  @file     memory_manager.h
  @brief    Memory System header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>

#include "file_system_manager.h"

#include "fsl_sd.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
#include "fsl_sysmpu.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART 0 transmit data source select: UART0_TX pin */


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool SD_connected = false;
static bool SD_error = false;
static bool SD_HostInitDone = false;
static TREE_NODE_T * rootNode;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void Mm_OnConnection(void);
static void Mm_Callback(bool isInserted, void *userData);
static void Mm_ScanFiles(char * path);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void Mm_Init(void)
{
	rootNode = getRootNode();

	SYSMPU_Enable(SYSMPU, false);

	CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

	const port_pin_config_t port_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAlt4,                                           /* Pin is configured as SDHC0_D1 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	};

	PORT_SetPinConfig(PORTE, PIN0_IDX, &port_config);   /* PORTE0 (pin 1) is configured as SDHC0_D1 */
	PORT_SetPinConfig(PORTE, PIN1_IDX, &port_config);   /* PORTE1 (pin 2) is configured as SDHC0_D0 */
	PORT_SetPinConfig(PORTE, PIN2_IDX, &port_config);   /* PORTE2 (pin 3) is configured as SDHC0_DCLK */
	PORT_SetPinConfig(PORTE, PIN3_IDX, &port_config);   /* PORTE3 (pin 4) is configured as SDHC0_CMD */
	PORT_SetPinConfig(PORTE, PIN4_IDX, &port_config);   /* PORTE4 (pin 5) is configured as SDHC0_D3 */
	PORT_SetPinConfig(PORTE, PIN5_IDX, &port_config);   /* PORTE5 (pin 6) is configured as SDHC0_D2 */

	const port_pin_config_t porte6_pin7_config = {
			kPORT_PullDown,                                          /* Internal pull-down resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTE6 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	};
	PORT_SetPinConfig(PORTE, PIN6_IDX, &porte6_pin7_config);   /* PORTE6 (pin 7) is configured as PTE6 */

	BOARD_SD_Config(&g_sd, Mm_Callback, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

	if (SD_HostInit(&g_sd) != kStatus_Success)
	{
		printf("\r\nSD host init fail\r\n");
		SD_error = true;
	}

	SD_SetCardPower(&g_sd, false);

	SD_HostInitDone = true;

	if(SD_connected)
	{
		Mm_OnConnection();
	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



static void Mm_Callback(bool isInserted, void *userData)
{
	SD_connected = isInserted;
	if(SD_HostInitDone)
	{
		Mm_OnConnection();
	}
}
static void Mm_OnConnection(void)
{
	FATFS g_fileSystem;
	FRESULT error;
	const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};

	if(!SD_connected || !SD_HostInitDone)
	{
		return;
	}


	if (SD_CardInit(&g_sd)) // tiene que arrancar la SD afuera
	{
		printf("\r\nSD card init failed.\r\n");
		SD_error = true;
	}

	if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
	{
		printf("Mount volume failed.\r\n");
		SD_error = true;
	}

    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
	if (error)
	{
		printf("Change drive failed.\r\n");
		return;
	}

	printf("\r\nList the file in that directory......\r\n");

	char buff[100];
	for (int i = 0; i<100;i++){buff[i] = 0;}
	//buff[0] = 0;
	Mm_ScanFiles(buff);

	printTree(rootNode, "", true);
}


static void Mm_ScanFiles(char * path)
{
	FRESULT error;
	DIR directory; /* Directory object */
	FILINFO fileInformation;

	if (f_opendir(&directory, path))
	{
		printf("Open directory failed.\r\n");
		return;
	}
	for (;;)
	{
		error = f_readdir(&directory, &fileInformation);
		if ((error != FR_OK) || (fileInformation.fname[0U] == 0U))
		{
			break;
		}
		if (fileInformation.fname[0] == '.')
		{
			continue;
		}
		if (fileInformation.fattrib & AM_DIR)
		{
			int i = strlen(path);
			char * fn = fileInformation.fname;
			*(path+i) = '/'; strcpy(path+i+1, fn);
			Mm_ScanFiles(path);
			*(path+i) = 0;
		}
		else
		{


			int i = strlen(path);
			char * fn = fileInformation.fname;
			*(path+i) = '/'; strcpy(path+i+1, fn);

			printf("General file : %s.\r\n", path);

			//if (isMp3File(path))
				addFileToTree(path);

			*(path+i) = 0;
		}
	}
	f_closedir(&directory);
}
