/*
 * rotary_encoder.h
 *
 *  Created on: Dec 5, 2025
 *      Author: jondbaker
 */

#ifndef INC_ROTARY_ENCODER_H_
#define INC_ROTARY_ENCODER_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32c0xx_hal.h"

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE (-1)

typedef struct {
	GPIO_TypeDef *clk_port;
	uint16_t      clk_pin;
	GPIO_TypeDef *dt_port;
	uint16_t      dt_pin;
	uint8_t       prevNextCode; // TODO make private
	uint16_t      store; // TODO make private
} RotaryEncoder;

int8_t read_encoder(RotaryEncoder *inc_enc);

#endif /* INC_ROTARY_ENCODER_H_ */
