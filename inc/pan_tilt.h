/*
 * pan_tilt.h
 *
 *  Created on: Dec 11, 2025
 *      Author: jondbaker
 */

#ifndef INC_PAN_TILT_H_
#define INC_PAN_TILT_H_

#include "stm32_encoder.h"
#include "servo.h"

typedef struct {
    Stm32Encoder encoder;
    Servo servo;
} AxisController;

typedef struct {
    AxisController pan;
    AxisController tilt;
} PanTilt;

PanTilt PanTilt_init(Stm32Encoder pan_encoder, Servo pan_servo, Stm32Encoder tilt_encoder, Servo tilt_servo);

void PanTilt_reset(PanTilt *pan_tilt);

void PanTilt_update(AxisController *axis);

#endif /* INC_PAN_TILT_H_ */
