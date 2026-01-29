//
// Created by jondbaker on 1/29/26.
//

#ifndef PAN_TILT_CTRL_STM32_CLOCK_H
#define PAN_TILT_CTRL_STM32_CLOCK_H

#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_rcc.h"

void clock_init(void(*Error_Handler)(void));

#endif //PAN_TILT_CTRL_STM32_CLOCK_H