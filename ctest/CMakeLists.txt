cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

add_executable(ctest_exe_encoder test_encoder.c)
target_link_libraries(ctest_exe_encoder LINK_PUBLIC unity encoder_lib)
add_test(NAME ctest_encoder COMMAND ctest_exe_encoder)
set_tests_properties(ctest_encoder PROPERTIES PASS 0)

add_executable(ctest_exe_servo test_servo.c)
target_link_libraries(ctest_exe_servo LINK_PUBLIC unity servo_lib)
add_test(NAME ctest_servo COMMAND ctest_exe_servo)
set_tests_properties(ctest_servo PROPERTIES PASS 0)