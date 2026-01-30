#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"

extern osThreadId_t default_task_handle;

void default_task(void *argument);

void freertos_init(void); /* (MISRA C 2004 rule 8.1) */

#endif /* __APP_FREERTOS_H */
