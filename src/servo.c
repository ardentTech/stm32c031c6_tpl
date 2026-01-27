#include "servo.h"

#define DEGREES_PER_STEP 5
#define MAX_ROTATION_DEGREES 180

static uint16_t angle_to_pulse(const Stm32Servo *servo, uint16_t angle);

static void servo_update_position(Stm32Servo *servo, uint16_t position_us);

Stm32Servo servo_init(
    TIM_HandleTypeDef *timer,
    const uint32_t channel,
    const uint16_t min_position_us,
    const uint16_t max_position_us
) {
    return (Stm32Servo){timer, channel, min_position_us, max_position_us, 0};
}

void servo_reset(Stm32Servo *servo) {
    servo_rotate(servo, MAX_ROTATION_DEGREES / 2);
}

// rotates the servo to a specific angle
void servo_rotate(Stm32Servo *servo, const uint16_t angle) {
    assert_param(angle <= MAX_ROTATION_DEGREES);
    const uint16_t new_position = angle_to_pulse(servo, angle) + servo->min_position_us;
    servo_update_position(servo, new_position);
}

void servo_step_cw(Stm32Servo *servo) {
    uint16_t new_position = servo->position_us - angle_to_pulse(servo, DEGREES_PER_STEP);
    if (new_position < servo->min_position_us) {
        new_position = servo->min_position_us;
    }
    servo_update_position(servo, new_position);
}

void servo_step_ccw(Stm32Servo *servo) {
    uint16_t new_position = servo->position_us + angle_to_pulse(servo, DEGREES_PER_STEP);
    if (new_position > servo->max_position_us) {
        new_position = servo->max_position_us;
    }
    servo_update_position(servo, new_position);
}

static uint16_t angle_to_pulse(const Stm32Servo *servo, const uint16_t angle) {
    return angle * (servo->max_position_us - servo->min_position_us) / MAX_ROTATION_DEGREES;
}

static void servo_update_position(Stm32Servo *servo, const uint16_t position_us) {
    if (position_us != servo->position_us) {
        __HAL_TIM_SET_COMPARE(servo->timer, servo->channel, position_us);
        servo->position_us = position_us;
    }
}
