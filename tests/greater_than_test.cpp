#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(greater_than_test, ShouldReturnTrueWhenGreaterThan) {
    const auto program = "(> 20 10)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(greater_than_test, ShouldReturnFalseWhenNotGreaterThan) {
    const auto program = "(> 10 20)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(greater_than_test, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenGreaterThan) {
    const auto program = "(> 3.5 3.4)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(greater_than_test, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotGreaterThan) {
    const auto program = "(> 3.01 3.5)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(greater_than_test, ShouldReturnTrueWhenComparingOneNumber) {
    const auto program = "(> 2)";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(greater_than_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto program = "(>)";

    bool errorIsThrown = false;
    std::string message;

    try {
        run_program(program);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid number of arguments for function \">\", Expected at least 1, got 0");
}

