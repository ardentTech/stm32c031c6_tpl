#include "pan_tilt.h"

PanTilt pantilt_init(Stm32Encoder pan_encoder, Stm32Servo pan_servo, Stm32Encoder tilt_encoder, Stm32Servo tilt_servo) {
    const AxisController pan = (AxisController){pan_encoder, pan_servo};
    const AxisController tilt = (AxisController){tilt_encoder, tilt_servo};
    return (PanTilt){pan, tilt};
}

void pantilt_reset(PanTilt *pan_tilt) {
    servo_rotate(&pan_tilt->pan.servo, 90);
    servo_rotate(&pan_tilt->tilt.servo, 90);
}

void pantilt_update(AxisController *axis) {
    switch (stm32_encoder_read(&axis->encoder)) {
        case CLOCKWISE:
            servo_step_cw(&axis->servo);
            break;
        case COUNTERCLOCKWISE:
            servo_step_ccw(&axis->servo);
            break;
        default: break;
    }
}
