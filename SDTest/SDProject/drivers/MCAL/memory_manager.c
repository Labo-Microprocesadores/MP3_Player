/***************************************************************************/ /**
  @file     memory_manager.h
  @brief    Memory System header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "file_system_manager.h"

#include <stdio.h>

#include "fsl_port.h"
#include "fsl_sd.h"
#include "fsl_sd_disk.h"

#include "ff.h"
#include "diskio.h"
#include "sdmmc_config.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool SD_connected = false;
static bool SD_error = false;
static bool SD_HostInitDone = false;
static FATFS g_fileSystem;
static Mp3File_t firstFile;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void Mm_OnConnection(void);
static void Mm_OnDesconection(void);
static void Mm_Callback(bool isInserted, void *userData);
static void Mm_ScanFiles(char * path);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void Mm_Init(void)
{
	firstFile = FileSystem_GetFirstFile();
	SYSMPU->CESR &= ~SYSMPU_CESR_VLD_MASK;

	BOARD_SD_Config(&g_sd, Mm_Callback, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

	if (SD_HostInit(&g_sd) != kStatus_Success)
	{
		printf("\r\nSD host init fail\r\n");
		SD_error = true;
	}

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
	if(SD_connected == isInserted)
	{
		SD_error = true;
	}
	else if(SD_HostInitDone && isInserted)
	{
		Mm_OnConnection();
	}
	else if(SD_HostInitDone && !isInserted)
	{
		Mm_OnDesconection();
	}

	SD_connected = isInserted;
}

static void Mm_OnDesconection(void)
{
	const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
	f_mount(NULL, driverNumberBuffer, 1U);
	g_sd.initReady = false;
	firstFile = FileSystem_ResetFiles();
	printf("fuera\r\n");
}

static void Mm_OnConnection(void)
{
	FRESULT error;
	const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};

	if (f_mount(&g_fileSystem, driverNumberBuffer, 1U))
	{
		printf("Mount volume failed.\r\n");
		SD_error = true;
		return;
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

	Mm_ScanFiles(buff);

	//FileSystem_PrintFiles(true);
	printf("Fin\r\n");
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

			if (FileSystem_isMp3File(path))
				FileSystem_AddFile(path);

			*(path+i) = 0;
		}
	}
	f_closedir(&directory);
}
