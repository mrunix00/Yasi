#include "boilerplate.h"

TEST(less_than_test, ShouldReturnTrueWhenLessThan) {
    const auto program = "(< 10 20)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(less_than_test, ShouldReturnFalseWhenNotLessThan) {
    const auto program = "(< 20 10)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(less_than_test, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenLessThan) {
    const auto program = "(< 3.4 3.5)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(less_than_test, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotLessThan) {
    const auto program = "(< 3.5 3.14)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
