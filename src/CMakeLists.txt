add_executable(tpl
        app_freertos.c
        main.c
        startup_stm32c031c6tx.s
        stm32c0xx_hal_msp.c
        stm32c0xx_hal_timebase_tim.c
        stm32c0xx_it.c
        stm32c0xx_nucleo.c
        syscalls.c
        sysmem.c
        system_stm32c0xx.c
)

target_link_libraries(tpl PUBLIC freertos)
target_link_libraries(tpl PUBLIC cmsis6)
target_link_libraries(tpl PUBLIC stm32)

target_include_directories(tpl PUBLIC
        ../inc
)

add_compile_definitions(USE_NUCLEO_64 USE_HAL_DRIVER STM32C031xx)