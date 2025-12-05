#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"

typedef struct
{
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temp_int;
    uint8_t temp_dec;
    uint8_t checksum;
} DHT11_Data_TypeDef;

void DHT11_Init(void);
uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data);

#endif
