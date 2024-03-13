#include "boilerplate.h"

TEST(divide_test, ShouldDivideTwoLiterals) {
    const auto program = "(/ 30 2)";

    const auto expected_result = StackObject((double) 15);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(divide_test, ShouldDivideTwoDecimalNumbers) {
    const auto program = "(/ 4.5 1.5)";

    const auto expected_result = StackObject((double) 3);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(divide_test, ShouldAddDecimalAndIntegerNumbers) {
    const auto program = "(/ 4.5 2)";

    const auto expected_result = StackObject(2.25);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
