/*
 * rotary_encoder.c
 *
 *  Created on: Dec 5, 2025
 *      Author: jondbaker
 */

#include "rotary_encoder.h"

// TODO unit test
// ref: https://www.best-microcontroller-projects.com/rotary-encoder.html
int8_t read_encoder(RotaryEncoder *rot_enc) {
	static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

	rot_enc->prevNextCode <<= 2;
	if (HAL_GPIO_ReadPin(rot_enc->dt_port, rot_enc->dt_pin) == GPIO_PIN_RESET) rot_enc->prevNextCode |= 0x02;
	if (HAL_GPIO_ReadPin(rot_enc->clk_port, rot_enc->clk_pin) == GPIO_PIN_RESET) rot_enc->prevNextCode |= 0x01;
	rot_enc->prevNextCode &= 0x0f;

	if (rot_enc_table[rot_enc->prevNextCode] ) { // valid output sequence
		rot_enc->store <<= 4;
		rot_enc->store |= rot_enc->prevNextCode;
		if ((rot_enc->store & 0xff) == 0x2b) {
			return COUNTER_CLOCKWISE;
		}
		if ((rot_enc->store & 0xff) == 0x17) {
			return CLOCKWISE;
		}
	}
	return 0;
}
