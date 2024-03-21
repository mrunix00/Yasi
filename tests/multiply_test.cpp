#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

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

TEST(multiply_test, ShouldReturnTheSameNumberWhenMultiplyingOneNumber) {
    const auto expression = "(* 3.1415)";

    const auto expected_result = StackObject((double) 3.1415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(multiply_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto expression = "(*)";

    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        message = e.message;
    }
    EXPECT_EQ(message, "Invalid number of arguments for function \"*\", Expected at least 1, got 0");
}

TEST(multiply_test, ShouldThrowAnErrorWhenInvalidArgumentIsPasseg) {
    const auto expression = "(* 10 \"Hello World\")";

    bool errorIsThrown = false;
    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }
    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid argument type for function \"*\", Expected number, got string");
}
