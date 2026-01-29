#include <FreeRTOS.h>
#include <semphr.h>
#include "main.h"

#include "cmsis_os2.h"
#include "pan_tilt.h"
#include "stm32_encoder.h"
#include "stm32_servo.h"
#include "stm32_tim.h"

TIM_HandleTypeDef htim3;
static PanTilt pan_tilt;

void pan_encoder_task_init(void);
void pan_encoder_task_notify(void);
void tilt_encoder_task_init(void);
void tilt_encoder_task_notify(void);

TaskHandle_t pan_encoder_task_handle;
TaskHandle_t tilt_encoder_task_handle;

// these values are from manually testing the two Tower SG90s in the adafruit pan+tilt kit
const uint16_t PAN_MIN_PULSE = 500;
const uint16_t PAN_MAX_PULSE = 2400;
const uint16_t TILT_MIN_PULSE = 1300;
const uint16_t TILT_MAX_PULSE = 2400;

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
static void MX_GPIO_Init(void);
//static void MX_TIM3_Init(void);
void pan_encoder_task(void *argument);
void tilt_encoder_task(void *argument);

void pan_encoder_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        /* Sleep until we are notified of a state change by an
        * interrupt handler. Note the first parameter is pdTRUE,
        * which has the effect of clearing the task's notification
        * value back to 0, making the notification value act like
        * a binary (rather than a counting) semaphore.  */
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            pantilt_update(&pan_tilt.pan);
        }
        // TODO i don't think an explicit delay is needed
    }
}

void tilt_encoder_task(void *argument) {
    static uint32_t thread_notification;
    while (1) {
        /* Sleep until we are notified of a state change by an
        * interrupt handler. Note the first parameter is pdTRUE,
        * which has the effect of clearing the task's notification
        * value back to 0, making the notification value act like
        * a binary (rather than a counting) semaphore.  */
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (thread_notification) {
            pantilt_update(&pan_tilt.tilt);
        }
        // TODO i don't think an explicit delay is needed
    }
}

void pan_encoder_task_notify() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Notify the thread so it will wake up when the ISR is complete
    vTaskNotifyGiveFromISR(pan_encoder_task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void tilt_encoder_task_notify() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // Notify the thread so it will wake up when the ISR is complete
    vTaskNotifyGiveFromISR(tilt_encoder_task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == PAN_CLK_Pin || GPIO_Pin == PAN_DT_Pin) {
        pan_encoder_task_notify();
    }
    if (GPIO_Pin == TILT_CLK_Pin || GPIO_Pin == TILT_DT_Pin) {
        tilt_encoder_task_notify();
    }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == PAN_CLK_Pin || GPIO_Pin == PAN_DT_Pin) {
        pan_encoder_task_notify();
    }
    if (GPIO_Pin == TILT_CLK_Pin || GPIO_Pin == TILT_DT_Pin) {
        tilt_encoder_task_notify();
    }
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */

    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin : TILT_CLK_Pin */
    GPIO_InitStruct.Pin = TILT_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(TILT_CLK_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : TILT_DT_Pin PAN_DT_Pin PAN_CLK_Pin */
    GPIO_InitStruct.Pin = TILT_DT_Pin|PAN_DT_Pin|PAN_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

// static void MX_TIM3_Init(void) {
//     TIM_MasterConfigTypeDef sMasterConfig = {0};
//     TIM_OC_InitTypeDef sConfigOC = {0};
//     htim3.Instance = TIM3;
//     htim3.Init.Prescaler = 48-1;
//     htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//     htim3.Init.Period = 20000-1;
//     htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//     htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//     if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
//         Error_Handler();
//     }
//     sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//     sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//     if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
//         Error_Handler();
//     }
//     sConfigOC.OCMode = TIM_OCMODE_PWM1;
//     sConfigOC.Pulse = 0;
//     sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//     sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//     if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
//         Error_Handler();
//     }
//     if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
//         Error_Handler();
//     }
//     HAL_TIM_Base_Start(&htim3);
//     if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK) {
//         Error_Handler();
//     }
//     if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK) {
//         Error_Handler();
//     }
//     HAL_TIM_MspPostInit(&htim3);
// }

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        HAL_IncTick();
    }
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {}
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    tim3_init(&htim3, Error_Handler);

    const Stm32Encoder pan_encoder = stm32_encoder_init(PAN_CLK_GPIO_Port, PAN_CLK_Pin, PAN_DT_GPIO_Port, PAN_DT_Pin);
    const Stm32Encoder tilt_encoder = stm32_encoder_init(TILT_CLK_GPIO_Port, TILT_CLK_Pin, TILT_DT_GPIO_Port, TILT_DT_Pin);
    const Stm32Servo pan_servo = servo_init(&htim3, TIM_CHANNEL_1, PAN_MIN_PULSE, PAN_MAX_PULSE);
    const Stm32Servo tilt_servo = servo_init(&htim3, TIM_CHANNEL_2, TILT_MIN_PULSE, TILT_MAX_PULSE);
    pan_tilt = pantilt_init(pan_encoder, pan_servo, tilt_encoder, tilt_servo);
    pantilt_reset(&pan_tilt);

    pan_encoder_task_init();
    tilt_encoder_task_init();

    osKernelInitialize();

    MX_FREERTOS_Init();
    osKernelStart();

    // should never get here
    while (1) {}
}

void pan_encoder_task_init() {
    const osThreadAttr_t panEncoderTask_attributes = {
        .name = "panEncoderTask",
        .priority = (osPriority_t) osPriorityNormal + 2,
        .stack_size = 128 * 4
    };
    pan_encoder_task_handle = osThreadNew(pan_encoder_task, NULL, &panEncoderTask_attributes);
}

void tilt_encoder_task_init() {
    const osThreadAttr_t tiltEncoderTask_attributes = {
        .name = "tiltEncoderTask",
        .priority = (osPriority_t) osPriorityNormal + 1,
        .stack_size = 128 * 4
    };
    tilt_encoder_task_handle = osThreadNew(tilt_encoder_task, NULL, &tiltEncoderTask_attributes);
}

void assert_failed(uint8_t *file, uint32_t line) {
    // TODO should this just call into Error_Handler?
    GPIOA->BSRR = GPIO_BSRR_BS5;
}