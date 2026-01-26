add_library(servo_lib STATIC
        servo.c
)

target_include_directories(servo_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)