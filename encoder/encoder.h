//
// Created by jondbaker on 1/24/26.
//

#ifndef PAN_TILT_CTRL_ENCODER_H
#define PAN_TILT_CTRL_ENCODER_H

#include <inttypes.h>

typedef enum {
    COUNTERCLOCKWISE = -1,
    NONE = 0,
    CLOCKWISE = 1,
} RotationDirection;

typedef enum {
    LOW = 0,
    HIGH = 1,
} LogicLevel;

typedef struct {
    uint8_t       prevNextCode;
    uint16_t      store;
} EncoderState;

// TODO eventually this will return a struct with rotation and velocity
RotationDirection encoder_process(EncoderState *state, LogicLevel clock_signal, LogicLevel data_signal);

#endif //PAN_TILT_CTRL_ENCODER_H