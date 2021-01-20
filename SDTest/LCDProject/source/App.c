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
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static bool work = true;

#define ENABLE(x)  	((x)<<1)
#define RS(x)		(x)
#define VAL(x)		((x)<<4)

#define BLOCK(e, rs, v) 	(ENABLE(e) | RS(rs) | VAL(v))

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init(void)
{
	SPI_Init(SPI_0_ID, SPI_SLAVE_0, 700000U);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run(void)
{
	char msg[3] = {0U};
	if(work)
	{
		char c = getchar();
		if(c >= '0' && c<= '9')
		{
			c = c-'0';
			msg[0] = ENABLE(0) | VAL(c);
			msg[1] = ENABLE(1) | VAL(c);
			msg[2] = ENABLE(0) | VAL(c);

			SPI_Send(SPI_0_ID, SPI_SLAVE_0, msg, 3);
		}
	}
}








