add_executable(app
        app_freertos.c
        main.c
        pan_tilt.c
        rotary_encoder.c
        servo.c
        stm32c0xx_hal_msp.c
        stm32c0xx_hal_timebase_tim.c
        stm32c0xx_it.c
        syscalls.c
        sysmem.c
)

target_link_libraries(app PUBLIC freertos)
target_link_libraries(app PUBLIC cmsis6)
target_link_libraries(app PUBLIC stm32)
target_link_libraries(app PUBLIC encoder_lib)

target_include_directories(app PUBLIC
        ../inc
)

add_compile_definitions(USE_NUCLEO_64 USE_HAL_DRIVER STM32C031xx)