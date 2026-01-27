#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include <stdint.h>
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_tim.h"

typedef struct {
    TIM_HandleTypeDef *timer;
    uint32_t channel;
    uint16_t min_position_us;
    uint16_t max_position_us;
    uint16_t position_us;
} Stm32Servo;

Stm32Servo servo_init(
    TIM_HandleTypeDef *timer,
    uint32_t channel,
    uint16_t min_position_us,
    uint16_t max_position_us
);

void servo_reset(Stm32Servo *servo);
void servo_rotate(Stm32Servo *servo, uint16_t angle);
void servo_step_cw(Stm32Servo *servo);
void servo_step_ccw(Stm32Servo *servo);

#endif /* INC_SERVO_H_ */
