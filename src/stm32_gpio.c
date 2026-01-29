//
// Created by jondbaker on 1/29/26.
//
#include "stm32_gpio.h"

void EXTI2_3_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(TILT_DT_Pin);
}

void EXTI4_15_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(PAN_DT_Pin);
    HAL_GPIO_EXTI_IRQHandler(PAN_CLK_Pin);
    HAL_GPIO_EXTI_IRQHandler(TILT_CLK_Pin);
}