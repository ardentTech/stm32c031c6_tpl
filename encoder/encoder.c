//
// Created by jondbaker on 1/24/26.
//
#include "encoder.h"

// TODO should this return a count instead of a direction?
RotationDirection encoder_process(
    EncoderState *state,
    const LogicLevel clock_signal,
    const LogicLevel data_signal
) {
    static uint8_t state_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
    RotationDirection res = NONE;

    state->prevNextCode <<= 2;
    if (clock_signal == HIGH) {
        state->prevNextCode |= 0x02;
    }
    if (data_signal == HIGH) {
        state->prevNextCode |= 0x01;
    }
    state->prevNextCode &= 0x0f;

    if (state_table[state->prevNextCode]) {
        state->store <<= 4;
        state->store |= state->prevNextCode;
        if ((state->store & 0xff) == 0x2b) {
            res = COUNTERCLOCKWISE;
        }
        if ((state->store & 0xff) == 0x17) {
            res = CLOCKWISE;
        }
    }
    return res;
}