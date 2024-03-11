#include "boilerplate.h"

TEST(vm_greater_than, ShouldReturnTrueWhenGreaterThan) {
    const auto program = "(> 20 10)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_greater_than, ShouldReturnFalseWhenNotGreaterThan) {
    const auto program = "(> 10 20)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_greater_than, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenGreaterThan) {
    const auto program = "(> 3.5 3.4)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_greater_than, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotGreaterThan) {
    const auto program = "(> 3.01 3.5)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
