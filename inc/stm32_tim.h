//
// Created by jondbaker on 1/29/26.
//

#ifndef PAN_TILT_CTRL_STM32_TIM_H
#define PAN_TILT_CTRL_STM32_TIM_H

#include "stm32c0xx_hal_tim.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void tim3_init(TIM_HandleTypeDef* htim3, void (*Error_Handler)(void));

#endif //PAN_TILT_CTRL_STM32_TIM_H