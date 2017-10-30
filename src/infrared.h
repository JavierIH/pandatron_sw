#ifndef INFRARED_H
#define INFRARED_H

#include "stm32f1xx_hal.h"

uint32_t _adc_buf[8];

DMA_HandleTypeDef hdma_adc1;
ADC_HandleTypeDef hadc1;
ADC_ChannelConfTypeDef _sConfig;

void IR_Init();
uint32_t get_ir(uint8_t ir);


#endif // INFRARED_H
