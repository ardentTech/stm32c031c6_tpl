//
// Created by jondbaker on 1/25/26.
//

#ifndef PAN_TILT_CTRL_SERVO_H
#define PAN_TILT_CTRL_SERVO_H

#include <stdint.h>

typedef struct {
    uint16_t min_position_us;
    uint16_t max_position_us;
    uint16_t position_us;
} ServoState;

void servo_update_position(ServoState *state, uint16_t position_us, void (*callback)(ServoState*));

#endif //PAN_TILT_CTRL_SERVO_H