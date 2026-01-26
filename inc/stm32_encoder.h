//
// Created by jondbaker on 1/26/26.
//

#ifndef PAN_TILT_CTRL_STM32_ENCODER_H
#define PAN_TILT_CTRL_STM32_ENCODER_H

#include <stdint.h>
#include "stm32c0xx_hal.h"
#include "encoder.h"

typedef struct {
    GPIO_TypeDef *clk_port;
    uint16_t      clk_pin;
    GPIO_TypeDef *dt_port;
    uint16_t      dt_pin;
    EncoderState state;
} Stm32Encoder;

Stm32Encoder stm32_encoder_init(GPIO_TypeDef* clk_port,uint16_t clk_pin, GPIO_TypeDef* dt_port, uint16_t dt_pin);
RotationDirection stm32_encoder_read(Stm32Encoder* encoder);

#endif //PAN_TILT_CTRL_STM32_ENCODER_H