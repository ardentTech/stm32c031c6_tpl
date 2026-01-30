#include "app_freertos.h"

osThreadId_t default_task_handle;
const osThreadAttr_t default_task_attributes = {
		.name = "defaultTask",
		.priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4
};

void freertos_init(void) {
	default_task_handle = osThreadNew(default_task, NULL, &default_task_attributes);
}

void default_task(void *argument) {
	for(;;) {
		osDelay(1);
	}
}

