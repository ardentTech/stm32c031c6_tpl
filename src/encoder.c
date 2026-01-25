//
// Created by jondbaker on 1/24/26.
//

#include "encoder.h"

RotationDirection encoder_process(EncoderState *state, const LogicLevel clock, const LogicLevel data) {
    static uint8_t state_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
    RotationDirection res = NONE;

    state->prevNextCode <<= 2;
    if (clock == HIGH) {
        state->prevNextCode |= 0x02;
    }
    if (data == HIGH) {
        state->prevNextCode |= 0x01;
    }
    // clear 4 MSBs
    state->prevNextCode &= 0x0f;

    if (state_table[state->prevNextCode]) { // if sequence is valid
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