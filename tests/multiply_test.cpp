#include "boilerplate.h"

TEST(multiply_test, ShouldMultiplyTwoLiterals) {
    const auto program = "(* 20 10)";

    const auto expected_result = StackObject((double) 200);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(multiply_test, ShouldMultiplyTwoDecimalNumbers) {
    const auto program = "(* 3.1415 1.1)";

    const auto expected_result = StackObject(3.45565);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(multiply_test, ShouldMultiplyDecimalAndIntegerNumbers) {
    const auto program = "(* 3.1415 2)";

    const auto expected_result = StackObject(6.283);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
