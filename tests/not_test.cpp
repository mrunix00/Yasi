#include "boilerplate.h"

TEST(not_test, ShouldNegateATrueCondition) {
    const auto program = "(not (= 10 10))";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(not_test, ShouldNegateAFalseCondition) {
    const auto program = "(not (= 20 10))";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}