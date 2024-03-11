#include "boilerplate.h"

TEST(vm_less_than, ShouldReturnTrueWhenLessThan) {
    const auto program = "(< 10 20)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_less_than, ShouldReturnFalseWhenNotLessThan) {
    const auto program = "(< 20 10)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_less_than, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenLessThan) {
    const auto program = "(< 3.4 3.5)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_less_than, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotLessThan) {
    const auto program = "(< 3.5 3.14)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
