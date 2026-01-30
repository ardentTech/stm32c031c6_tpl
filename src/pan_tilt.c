#include "pan_tilt.h"

// Initializes the pan+tilt.
PanTilt pantilt_init(Stm32Encoder pan_encoder, Stm32Servo pan_servo, Stm32Encoder tilt_encoder, Stm32Servo tilt_servo) {
    const AxisController pan = (AxisController){pan_encoder, pan_servo};
    const AxisController tilt = (AxisController){tilt_encoder, tilt_servo};
    return (PanTilt){pan, tilt};
}

// Resets servos for both axes.
void pantilt_reset(PanTilt *pan_tilt) {
    servo_reset(&pan_tilt->pan.servo);
    servo_reset(&pan_tilt->tilt.servo);
}

// Resets an axis servo.
void pantilt_reset_servo(AxisController *axis) {
    servo_reset(&axis->servo);
}

// Reads the axis encoder and updates the axis servo if necessary.
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
