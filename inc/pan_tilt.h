#ifndef INC_PAN_TILT_H_
#define INC_PAN_TILT_H_

#include "stm32_encoder.h"
#include "stm32_servo.h"

typedef struct {
    Stm32Encoder encoder;
    Stm32Servo servo;
} AxisController;

typedef struct {
    AxisController pan;
    AxisController tilt;
} PanTilt;

PanTilt pantilt_init(Stm32Encoder pan_encoder, Stm32Servo pan_servo, Stm32Encoder tilt_encoder, Stm32Servo tilt_servo);

void pantilt_reset(PanTilt *pan_tilt);

void pantilt_update(AxisController *axis);

#endif /* INC_PAN_TILT_H_ */
