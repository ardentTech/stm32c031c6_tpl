add_executable(tpl
        main.c
        stm32c0xx_it.c
        stm32c0xx_hal_msp.c
        syscalls.c
        sysmem.c
)

target_link_libraries(tpl PUBLIC freertos)
target_link_libraries(tpl PUBLIC cmsis6)
target_link_libraries(tpl PUBLIC stm32)

target_include_directories(tpl PUBLIC
        ../inc
)