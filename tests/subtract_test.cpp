#include "boilerplate.h"

TEST(vm_subtract_test, ShouldSubtractTwoLiterals) {
    const auto program = "(- 30 20)";

    const auto expected_result = StackObject((double) 10);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_subtract_test, ShouldSubtractTwoDecimalNumbers) {
    const auto program = "(- 3.1415 1.1)";

    const auto expected_result = StackObject(2.0415);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_subtract_test, ShouldSubtractDecimalAndIntegerNumbers) {
    const auto program = "(- 3.1415 2)";

    const auto expected_result = StackObject(1.1415);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
