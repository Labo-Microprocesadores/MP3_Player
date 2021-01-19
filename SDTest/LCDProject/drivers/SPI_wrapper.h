/*
 * SPI_wrapper.h
 *
 *  Created on: 16 ene. 2021
 *      Author: Santi
 */

#ifndef SPI_WRAPPER_H_
#define SPI_WRAPPER_H_

typedef enum {
  SPI_0,
  SPI_1,
  SPI_2,
} spi_id_t;

typedef enum {
  SPI_SLAVE_0 = 0,
  SPI_SLAVE_1 = 4,
  SPI_SLAVE_2 = 3,
  SPI_SLAVE_3 = 2,
  SPI_SLAVE_4 = 1,
  SPI_SLAVE_5 = 23
} spi_slave_t;

void SPI_Init(spi_id_t id, spi_slave_t slave, uint32_t baudrate);

#endif /* SPI_WRAPPER_H_ */
