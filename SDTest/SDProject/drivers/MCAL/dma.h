/***************************************************************************/ /**
  @file     dma.h
  @brief    DMA Header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>

typedef enum
{
  DMA8_bits,
  DMA16_bits,
  DMA32_bits
} DMASize_t;

void DMA_Init(uint8_t channel, uint8_t dma_source, uint32_t source,
              uint32_t dest, uint8_t src_offset, uint8_t dest_offset,
              DMASize_t src_size, DMASize_t dest_size, uint32_t minorl_size,
              uint32_t mayorL_size, int16_t ret_after_ML, void (*callback)(void));

#endif /* DMA_H_ */
