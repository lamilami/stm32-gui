#ifndef __SPI_ENC28J60_H
#define __SPI_ENC28J60_H

#include "stm32f10x.h"


void SPI_Enc28j60_Init(void);
unsigned char	SPI2_ReadWrite(unsigned char writedat);

#endif /* __SPI_ENC28J60_H */
