#ifndef SPI_H
#define SPI_H

#include <stdint.h>

typedef struct
{
    volatile uint8_t *spcr;
    volatile uint8_t *spsr;
    volatile uint8_t *spdr;
}spi_t;

#endif // SPI_H
