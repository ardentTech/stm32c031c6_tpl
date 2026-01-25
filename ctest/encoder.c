//
// Created by jondbaker on 12/30/25.
//
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_demo() {
    TEST_ASSERT_EQUAL(0, 0);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_demo);

    return UNITY_END();
}