cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

add_executable(ctest_exe_addvalues_zero addvalues_zero.c)

target_link_libraries(ctest_exe_addvalues_zero LINK_PUBLIC
        unity
)

add_test(NAME ctest_addvalues_zero COMMAND ctest_exe_addvalues_zero)

set_tests_properties(ctest_addvalues_zero PROPERTIES PASS 0)

