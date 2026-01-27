cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

add_executable(ctest_exe_encoder test_encoder.c)
target_link_libraries(ctest_exe_encoder LINK_PUBLIC unity encoder_lib)
add_test(NAME ctest_encoder COMMAND ctest_exe_encoder)
set_tests_properties(ctest_encoder PROPERTIES PASS 0)