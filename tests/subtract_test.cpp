#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(subtract_test, ShouldSubtractTwoLiterals) {
    const auto program = "(- 30 20)";

    const auto expected_result = StackObject((double) 10);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(subtract_test, ShouldSubtractTwoDecimalNumbers) {
    const auto program = "(- 3.1415 1.1)";

    const auto expected_result = StackObject(2.0415);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(subtract_test, ShouldSubtractDecimalAndIntegerNumbers) {
    const auto program = "(- 3.1415 2)";

    const auto expected_result = StackObject(1.1415);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(subtract_test, ShouldReturnTheInverseOfTheNumberWhenGivenOneArgument) {
    const auto expression = "(- 3.1415)";

    const auto expected_result = StackObject((double) -3.1415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(subtract_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto expression = "(-)";

    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        message = e.message;
    }
    EXPECT_EQ(message, "Invalid number of arguments for function \"-\", Expected at least 1, got 0");
}

TEST(subtract_test, ShouldThrowAnErrorWhenInvalidArgumentIsPasseg) {
    const auto expression = "(- 10 \"Hello World\")";

    bool errorIsThrown = false;
    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }
    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid argument type for function \"-\", Expected number, got string");
}

