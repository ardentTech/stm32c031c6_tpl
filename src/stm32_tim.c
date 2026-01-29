//
// Created by jondbaker on 1/29/26.
//
#include "stm32c0xx_hal.h"
#include "stm32_tim.h"

void tim3_init(TIM_HandleTypeDef* htim3, void (*Error_Handler)(void)) {
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    htim3->Instance = TIM3;
    htim3->Init.Prescaler = 48-1;
    htim3->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3->Init.Period = 20000-1;
    htim3->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(htim3) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_PWM_ConfigChannel(htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
        Error_Handler();
    }
    HAL_TIM_Base_Start(htim3);
    if (HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_2) != HAL_OK) {
        Error_Handler();
    }
    HAL_TIM_MspPostInit(htim3);
}
