/***************************************************************************/ /**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <file_system_manager.h>
#include <stdio.h>
#include <stdbool.h>

#include "memory_manager.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/





/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{

	//testFileTree();

	printf("\r\nFATFS example to demonstrate how to use FATFS with SD card.\r\n");

	printf("\r\nPlease insert a card into board.\r\n");


	Mm_Init();

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{

}








