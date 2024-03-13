#include "boilerplate.h"

TEST(equals_test, ShouldReturnTrueOnEquality) {
    const auto program = "(= 10 10)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(equals_test, ShouldReturnFalseOnInequality) {
    const auto program = "(= 10 20)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(equals_test, ShouldCompareTwoDecimalNumbersAndReturnTrueOnEquality) {
    const auto program = "(= 3.5 3.5)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(equals_test, ShouldCompareTwoDecimalNumbersAndReturnFalseOnInequality) {
    const auto program = "(= 3.5 3.14)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
