//
// Created by jondbaker on 1/25/26.
//
#include "servo.h"

// TODO can make this static and still unit test?
uint16_t servo_angle_to_pulse(const ServoState *state, const uint16_t angle) {
    return angle * (state->max_position_us - state->min_position_us) / 180;
}

void servo_update_position(ServoState *state, const uint16_t position_us, void (*callback)(ServoState*)) {
    if (position_us != state->position_us) {
        state->position_us = position_us;
        callback(state);
    }
}

// TODO servo_pulse_to_angle?