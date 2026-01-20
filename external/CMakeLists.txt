# cmsis6
add_library(cmsis6 INTERFACE)
target_include_directories(cmsis6 INTERFACE
        cmsis6/CMSIS/RTOS2/Include
)

# freertos
set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/freertos")
add_library(freertos INTERFACE)
target_include_directories(freertos INTERFACE
        ${FREERTOS_DIR}/Source/include
        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM0
        ${FREERTOS_DIR}/CMSIS/RTOS2/FreeRTOS/Include
)
target_sources(freertos PUBLIC
        ${FREERTOS_DIR}/Source/list.c
        ${FREERTOS_DIR}/Source/queue.c
        ${FREERTOS_DIR}/Source/tasks.c
        ${FREERTOS_DIR}/Source/timers.c
        ${FREERTOS_DIR}/Source/portable/MemMang/heap_3.c
        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM0/port.c
        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM0/portasm.c
        ${FREERTOS_DIR}/CMSIS/RTOS2/FreeRTOS/Source/cmsis_os2.c
)

# stm32
add_library(stm32 INTERFACE)
target_include_directories(stm32 INTERFACE
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Inc
        stm32c0/Drivers/CMSIS/Include
        stm32c0/Drivers/CMSIS/Device/ST/STM32C0xx/Include
)
target_compile_definitions(stm32 INTERFACE
        STM32C031xx
)
target_sources(stm32 PUBLIC
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_adc.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_adc_ex.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_cortex.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_dma.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_gpio.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_rcc.c
        stm32c0/Drivers/STM32C0xx_HAL_Driver/Src/stm32c0xx_hal_uart.c
        stm32c0/Drivers/CMSIS/Device/ST/STM32C0xx/Source/Templates/system_stm32c0xx.c
        stm32c0/Drivers/CMSIS/Device/ST/STM32C0xx/Source/Templates/gcc/startup_stm32c031xx.s
)

# unity
add_library(unity STATIC
        unity/src/unity.c
)
target_include_directories(unity PUBLIC
        unity/src
)