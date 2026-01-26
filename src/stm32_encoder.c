//
// Created by jondbaker on 1/26/26.
//
#include "stm32_encoder.h"

Stm32Encoder stm32_encoder_init(GPIO_TypeDef* clk_port,uint16_t clk_pin, GPIO_TypeDef* dt_port, uint16_t dt_pin) {
    const EncoderState state = { 0, 0 };
    const Stm32Encoder encoder = (Stm32Encoder) { clk_port, clk_pin, dt_port, dt_pin, state };
    return encoder;
}

RotationDirection stm32_encoder_read(Stm32Encoder* encoder) {
    GPIO_PinState clk_state = HAL_GPIO_ReadPin(encoder->clk_port, encoder->clk_pin);
    GPIO_PinState dt_state = HAL_GPIO_ReadPin(encoder->dt_port, encoder->dt_pin);

    return encoder_process(
        &encoder->state,
        (LogicLevel) clk_state,
        (LogicLevel) dt_state
    );
}