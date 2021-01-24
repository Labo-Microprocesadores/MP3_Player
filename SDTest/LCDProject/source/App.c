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

#include "SPI_wrapper.h"
#include "LCD_GDM1602A.h"
#include "fsl_device_registers.h"

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
uint8_t a = 0;
/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
	LCD_Init();
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
	if(!a && LCD_isInit())
	{
		LCD_writeStrInPos(">", 1, 0, 0);
		LCD_writeBouncingStr("UnaCancion_Con nombre largo.mp3",31, 0, 1, SLOW);
		LCD_writeShiftingStr("Datos de la cancion, aurtor:...", 31, 1,FAST);
		a = 1;
	}
}








