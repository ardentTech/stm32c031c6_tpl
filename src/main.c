#include <FreeRTOS.h>
#include <task.h>

#include "cmsis_os2.h"
#include "error.h"
#include "pan_tilt.h"
#include "stm32_encoder.h"
#include "stm32_gpio.h"
#include "stm32_servo.h"
#include "stm32_sysclock.h"
#include "stm32_tim.h"

TIM_HandleTypeDef htim3;
static PanTilt pan_tilt;

void task_notify(TaskHandle_t task_handle);
void pan_btn_task_init(void);
void pan_encoder_task_init(void);
void tilt_btn_task_init(void);
void tilt_encoder_task_init(void);

TaskHandle_t pan_btn_task_handle;
TaskHandle_t pan_encoder_task_handle;
TaskHandle_t tilt_btn_task_handle;
TaskHandle_t tilt_encoder_task_handle;

// these values are from manually testing the two Tower SG90s in the adafruit pan+tilt kit
const uint16_t PAN_MIN_PULSE = 500;
const uint16_t PAN_MAX_PULSE = 2400;
const uint16_t TILT_MIN_PULSE = 1300;
const uint16_t TILT_MAX_PULSE = 2400;

void MX_FREERTOS_Init(void);
void pan_btn_task(void *argument);
void pan_encoder_task(void *argument);
void tilt_encoder_task(void *argument);
void tilt_btn_task(void *argument);

void pan_btn_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            servo_reset(&pan_tilt.pan.servo);
        }
    }
}

void pan_encoder_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            pantilt_update(&pan_tilt.pan);
        }
    }
}

void tilt_btn_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            servo_reset(&pan_tilt.tilt.servo);
        }
    }
}

void tilt_encoder_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            pantilt_update(&pan_tilt.tilt);
        }
    }
}

void task_notify(TaskHandle_t task_handle) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Notify the thread so it will wake up when the ISR is complete
    vTaskNotifyGiveFromISR(task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == PAN_CLK_Pin || GPIO_Pin == PAN_DT_Pin) {
        task_notify(pan_encoder_task_handle);
    }
    if (GPIO_Pin == TILT_CLK_Pin || GPIO_Pin == TILT_DT_Pin) {
        task_notify(tilt_encoder_task_handle);
    }
    if (GPIO_Pin == PAN_BTN_Pin) {
        task_notify(pan_btn_task_handle);
    }
    if (GPIO_Pin == TILT_BTN_Pin) {
        task_notify(tilt_btn_task_handle);
    }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == PAN_CLK_Pin || GPIO_Pin == PAN_DT_Pin) {
        task_notify(pan_encoder_task_handle);
    }
    if (GPIO_Pin == TILT_CLK_Pin || GPIO_Pin == TILT_DT_Pin) {
        task_notify(tilt_encoder_task_handle);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        HAL_IncTick();
    }
}

// Turn on on-board LED and enter black hole.
void error_handler(void) {
    __disable_irq();
    GPIOA->BSRR = GPIO_BSRR_BS5;
    while (1) {}
}

// Initializes the pan btn task.
void pan_btn_task_init() {
    const osThreadAttr_t panBtnTask_attributes = {
        .name = "panBtnTask",
        .priority = (osPriority_t) osPriorityNormal + 4,
        .stack_size = 128 * 4
    };
    pan_btn_task_handle = osThreadNew(pan_btn_task, NULL, &panBtnTask_attributes);
}

// Initializes the pan encoder task.
void pan_encoder_task_init() {
    const osThreadAttr_t panEncoderTask_attributes = {
        .name = "panEncoderTask",
        .priority = (osPriority_t) osPriorityNormal + 2,
        .stack_size = 128 * 4
    };
    pan_encoder_task_handle = osThreadNew(pan_encoder_task, NULL, &panEncoderTask_attributes);
}

// Initializes the tilt btn task.
void tilt_btn_task_init() {
    const osThreadAttr_t tiltBtnTask_attributes = {
        .name = "tiltBtnTask",
        .priority = (osPriority_t) osPriorityNormal + 3,
        .stack_size = 128 * 4
    };
    tilt_btn_task_handle = osThreadNew(tilt_btn_task, NULL, &tiltBtnTask_attributes);
}

// Initializes the tilt encoder task.
void tilt_encoder_task_init() {
    const osThreadAttr_t tiltEncoderTask_attributes = {
        .name = "tiltEncoderTask",
        .priority = (osPriority_t) osPriorityNormal + 1,
        .stack_size = 128 * 4
    };
    tilt_encoder_task_handle = osThreadNew(tilt_encoder_task, NULL, &tiltEncoderTask_attributes);
}

void assert_failed(uint8_t *file, uint32_t line) {
    error_handler();
}

int main(void) {
    HAL_Init();
    clock_init(error_handler);
    gpio_init();
    tim3_init(&htim3, error_handler);

    const Stm32Encoder pan_encoder = stm32_encoder_init(PAN_CLK_GPIO_Port, PAN_CLK_Pin, PAN_DT_GPIO_Port, PAN_DT_Pin);
    const Stm32Encoder tilt_encoder = stm32_encoder_init(TILT_CLK_GPIO_Port, TILT_CLK_Pin, TILT_DT_GPIO_Port, TILT_DT_Pin);

    const Stm32Servo pan_servo = servo_init(&htim3, TIM_CHANNEL_1, PAN_MIN_PULSE, PAN_MAX_PULSE);
    const Stm32Servo tilt_servo = servo_init(&htim3, TIM_CHANNEL_2, TILT_MIN_PULSE, TILT_MAX_PULSE);

    pan_tilt = pantilt_init(pan_encoder, pan_servo, tilt_encoder, tilt_servo);
    pantilt_reset(&pan_tilt); // start servos in neutral position

    pan_btn_task_init();
    pan_encoder_task_init();
    tilt_btn_task_init();
    tilt_encoder_task_init();

    osKernelInitialize();

    MX_FREERTOS_Init();
    osKernelStart();

    // should never get here
    while (1) {}
}