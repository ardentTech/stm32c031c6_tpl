/*
 * servo.c
 *
 *  Created on: Dec 6, 2025
 *      Author: jondbaker
 */

#include <inttypes.h>
#include <stdio.h>
#include "servo.h"

#define STEP_DEGREES 5

static uint16_t angle_to_pulse(const ServoState *servo, uint16_t angle);

static void Servo_update_position(ServoState *servo, uint16_t position_us);

ServoState Servo_init(
    TIM_HandleTypeDef *timer,
    const uint32_t channel,
    const uint16_t min_position_us,
    const uint16_t max_position_us
) {
    ServoState servo = (ServoState){timer, channel, min_position_us, max_position_us, 0, 0};
    servo.step_us = angle_to_pulse(&servo, STEP_DEGREES);
    return servo;
}

void Servo_rotate(ServoState *servo, const uint16_t angle) {
    const uint16_t new_position = angle_to_pulse(servo, angle) + servo->min_position_us;
    Servo_update_position(servo, new_position);
}

// TODO unit test
void Servo_step_cw(ServoState *servo) {
    uint16_t new_position = servo->position_us - servo->step_us;
    if (new_position < servo->min_position_us) {
        new_position = servo->min_position_us;
    }
    Servo_update_position(servo, new_position);
}

// TODO unit test
void Servo_step_ccw(ServoState *servo) {
    uint16_t new_position = servo->position_us + servo->step_us;
    if (new_position > servo->max_position_us) {
        new_position = servo->max_position_us;
    }
    Servo_update_position(servo, new_position);
}

// TODO unit test
static uint16_t angle_to_pulse(const ServoState *servo, const uint16_t angle) {
    return angle * (servo->max_position_us - servo->min_position_us) / 180;
}

// TODO unit test
static void Servo_update_position(ServoState *servo, const uint16_t position_us) {
    if (position_us != servo->position_us) {
        __HAL_TIM_SET_COMPARE(servo->timer, servo->channel, position_us);
        servo->position_us = position_us;
    }
}
