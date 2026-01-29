//
// Created by jondbaker on 1/29/26.
//

#ifndef PAN_TILT_CTRL_STM32_GPIO_H
#define PAN_TILT_CTRL_STM32_GPIO_H

#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_gpio.h"

#define PAN_BTN_Pin GPIO_PIN_5
#define PAN_BTN_GPIO_Port GPIOB
#define PAN_BTN_EXTI_IRQn EXTI4_15_IRQn

#define PAN_CLK_Pin GPIO_PIN_7
#define PAN_CLK_GPIO_Port GPIOB
#define PAN_CLK_EXTI_IRQn EXTI4_15_IRQn

#define PAN_DT_Pin GPIO_PIN_6
#define PAN_DT_GPIO_Port GPIOB
#define PAN_DT_EXTI_IRQn EXTI4_15_IRQn

#define TILT_BTN_Pin GPIO_PIN_15
#define TILT_BTN_GPIO_Port GPIOA
#define TILT_BTN_EXTI_IRQn EXTI4_15_IRQn

#define TILT_CLK_Pin GPIO_PIN_10
#define TILT_CLK_GPIO_Port GPIOA
#define TILT_CLK_EXTI_IRQn EXTI4_15_IRQn

#define TILT_DT_Pin GPIO_PIN_3
#define TILT_DT_GPIO_Port GPIOB
#define TILT_DT_EXTI_IRQn EXTI2_3_IRQn

void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void gpio_init(void);

#endif //PAN_TILT_CTRL_STM32_GPIO_H