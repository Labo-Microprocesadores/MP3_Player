/***************************************************************************/ /**
  @file     matrix display.h
  @brief    8x8 RGB display hearder
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef MATRIX_DISPLAY_H_
#define MATRIX_DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>

#define DISPLAY_SIZE 128

typedef struct
{
  bool R;
  bool G;
  bool B;
} pixel_t;

void md_Init(void);

void md_changeBackBuffer(void);

void md_writeBuffer(pixel_t *buffer);

pixel_t md_makeColor(bool R, bool G, bool B);

void md_setBrightness(uint8_t brigthness);

#endif /* MATRIX_DISPLAY_H_ */
 
