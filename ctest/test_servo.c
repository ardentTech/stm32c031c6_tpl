//
// Created by jondbaker on 1/25/26.
//
#include <unity.h>
#include "servo.h"

static uint16_t test_position_us = 0;

// framework
void setUp() {}
void tearDown() {}

// module
void nop_callback(ServoState* state) {}
void inc_callback(ServoState* state) {
    test_position_us = state->position_us;
}

void test_servo_update_position_callback() {
    const uint16_t new_position = 300;
    ServoState state = (ServoState) { 0, 0, 295 };
    TEST_ASSERT_EQUAL(0, test_position_us);
    servo_update_position(&state, new_position, &inc_callback);
    TEST_ASSERT_EQUAL(new_position, test_position_us);
}

void test_servo_update_position_no_change() {
    const uint16_t new_position = 800;
    ServoState state = (ServoState) { 0, 0, new_position };
    servo_update_position(&state, new_position, &nop_callback);
    TEST_ASSERT_EQUAL(state.position_us, new_position);
}

void test_servo_update_position_ok() {
    const uint16_t new_position = 1100;
    ServoState state = (ServoState) { 0, 0, 0 };
    servo_update_position(&state, new_position, &nop_callback);
    TEST_ASSERT_EQUAL(state.position_us, new_position);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_servo_update_position_callback);
    RUN_TEST(test_servo_update_position_no_change);
    RUN_TEST(test_servo_update_position_ok);

    return UNITY_END();
}