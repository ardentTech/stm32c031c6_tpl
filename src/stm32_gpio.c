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

void gpio_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */

    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin : TILT_CLK_Pin */
    GPIO_InitStruct.Pin = TILT_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(TILT_CLK_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : TILT_DT_Pin PAN_DT_Pin PAN_CLK_Pin */
    GPIO_InitStruct.Pin = TILT_DT_Pin|PAN_DT_Pin|PAN_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}