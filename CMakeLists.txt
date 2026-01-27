cmake_minimum_required(VERSION 4.1)
project(pan_tilt_ctrl C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

enable_language(C ASM)

add_subdirectory(external)
add_subdirectory(encoder)
if(CMAKE_BUILD_TYPE STREQUAL "Test")
    enable_testing() # this will include(CTest)
    add_subdirectory(ctest)
else()
    add_subdirectory(src)
endif()