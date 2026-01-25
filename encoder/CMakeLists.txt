add_library(encoder_lib STATIC
        encoder.c
)

target_include_directories(encoder_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)