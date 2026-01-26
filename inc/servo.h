/*
 * servo.h
 *
 *  Created on: Dec 6, 2025
 *      Author: jondbaker
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include <stdint.h>
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_tim.h"

typedef struct {
    TIM_HandleTypeDef *timer;
    uint32_t channel;
    uint16_t min_position_us;
    uint16_t max_position_us;
    uint16_t position_us;
    uint16_t step_us;
} ServoState;

ServoState Servo_init(
    TIM_HandleTypeDef *timer,
    uint32_t channel,
    uint16_t min_position_us,
    uint16_t max_position_us
);

void Servo_rotate(ServoState *servo, uint16_t angle);

void Servo_step_cw(ServoState *servo);

void Servo_step_ccw(ServoState *servo);

#endif /* INC_SERVO_H_ */
