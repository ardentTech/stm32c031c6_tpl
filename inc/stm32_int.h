//
// Created by jondbaker on 1/29/26.
//

#ifndef PAN_TILT_CTRL_STM32_INT_H
#define PAN_TILT_CTRL_STM32_INT_H

#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_tim.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);

#endif //PAN_TILT_CTRL_STM32_INT_H