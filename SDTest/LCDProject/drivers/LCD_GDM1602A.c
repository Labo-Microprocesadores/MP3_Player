/*
 * LCD_GDM1602A.c
 *
 *  Created on: 16 ene. 2021
 *      Author: Santi
 */


#include "SPI_wrapper.h"

void LCD_Init(void)
{
	SPI_Init(SPI_0_ID, SPI_SLAVE_0, uint32_t baudrate);
}
