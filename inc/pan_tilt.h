/*
 * pan_tilt.h
 *
 *  Created on: Dec 11, 2025
 *      Author: jondbaker
 */

#ifndef INC_PAN_TILT_H_
#define INC_PAN_TILT_H_

#include "rotary_encoder.h"
#include "servo.h"

typedef struct {
    RotaryEncoder encoder;
    Servo servo;
} AxisController;

typedef struct {
    AxisController pan;
    AxisController tilt;
} PanTilt;

PanTilt PanTilt_init(RotaryEncoder pan_encoder, ServoState pan_servo, RotaryEncoder tilt_encoder, ServoState tilt_servo);

void PanTilt_reset(PanTilt *pan_tilt);

void PanTilt_update(AxisController *axis);

#endif /* INC_PAN_TILT_H_ */
