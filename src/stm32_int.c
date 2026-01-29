//
// Created by jondbaker on 1/29/26.
//
#include "stm32_int.h"

extern TIM_HandleTypeDef htim1;

void NMI_Handler(void) {
    while (1) { }
}

void HardFault_Handler(void) {
    while (1) { }
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim1);
}