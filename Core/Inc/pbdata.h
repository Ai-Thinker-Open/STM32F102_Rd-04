#ifndef _pbdata_H
#define _pbdata_H

#include "stm32f1xx.h"

#include "stm32f1xx_hal_exti.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_usart.h"
#include "stdio.h"
#include "I2C.h"

extern uint8_t dt;

void delay_us(uint32_t nus);

#endif
