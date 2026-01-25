//
// Created by jondbaker on 12/30/25.
//
#include <unity.h>
#include "encoder.h"

void setUp() {}
void tearDown() {}

void test_encoder_cw() {
    EncoderState state = (EncoderState) { 0x1, 0x1 };
    const RotationDirection res = encoder_process(&state, HIGH, HIGH);
    TEST_ASSERT_EQUAL(CLOCKWISE, res);
}

void test_encoder_ccw() {
    EncoderState state = (EncoderState) { 0x2, 0x2 };
    const RotationDirection res = encoder_process(&state, HIGH, HIGH);
    TEST_ASSERT_EQUAL(COUNTERCLOCKWISE, res);
}

void test_encoder_none() {
    EncoderState state = (EncoderState) { 0, 0 };
    const RotationDirection res = encoder_process(&state, LOW, HIGH);
    TEST_ASSERT_EQUAL(NONE, res);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_encoder_cw);
    RUN_TEST(test_encoder_ccw);
    RUN_TEST(test_encoder_none);

    return UNITY_END();
}