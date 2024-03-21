#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

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

TEST(divide_test, ShouldReturnTheReciprocalOfTheNumberWhenDividingOneNumber) {
    const auto expression = "(/ 2)";

    const auto expected_result = StackObject((double) 0.5);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(divide_test, ShouldThrowAnErrorWhenDividingByZero) {
    const auto expression = "(/ 2 0)";

    std::string message;
    try {
    const auto actual_result = run_program(expression);
    } catch (const SyntaxError& e) {
        message = e.message;
    }

    EXPECT_EQ(message, "Division by zero");
}

TEST(divide_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto expression = "(/)";

    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        message = e.message;
    }
    EXPECT_EQ(message, "Invalid number of arguments for function \"/\", Expected at least 1, got 0");
}

TEST(divide_test, ShouldThrowAnErrorWhenInvalidArgumentIsPasseg) {
    const auto expression = "(/ 10 \"Hello World\")";

    bool errorIsThrown = false;
    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }
    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid argument type for function \"/\", Expected number, got string");
}

