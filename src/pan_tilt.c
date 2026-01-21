/*
 * pan_tilt.c
 *
 *  Created on: Dec 11, 2025
 *      Author: jondbaker
 */

#include "pan_tilt.h"

PanTilt PanTilt_init(RotaryEncoder pan_encoder, Servo pan_servo, RotaryEncoder tilt_encoder, Servo tilt_servo) {
    const AxisController pan = (AxisController){pan_encoder, pan_servo};
    const AxisController tilt = (AxisController){tilt_encoder, tilt_servo};
    return (PanTilt){pan, tilt};
}

void PanTilt_reset(PanTilt *pan_tilt) {
    Servo_rotate(&pan_tilt->pan.servo, 90);
    Servo_rotate(&pan_tilt->tilt.servo, 90);
}

void PanTilt_update(AxisController *axis) {
    switch (read_encoder(&axis->encoder)) {
        case CLOCKWISE:
            Servo_step_cw(&axis->servo);
            break;
        case COUNTER_CLOCKWISE:
            Servo_step_ccw(&axis->servo);
            break;
        default: break;
    }
}
