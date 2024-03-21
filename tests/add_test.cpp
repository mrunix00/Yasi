#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(add_test, ShouldAddTwoLiterals) {
    const auto expression = "(+ 10 20)";

    const auto expected_result = StackObject((double) 30);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(add_test, ShouldAddTwoDecimalNumbers) {
    const auto expression = "(+ 3.1415 1.5)";

    const auto expected_result = StackObject(4.6415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(add_test, ShouldAddDecimalAndIntegerNumbers) {
    const auto expression = "(+ 3.1415 1)";

    const auto expected_result = StackObject((double) 4.1415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(add_test, ShouldReturnTheSameNumberWhenAddingOneNumber) {
    const auto expression = "(+ 3.1415)";

    const auto expected_result = StackObject((double) 3.1415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(add_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto expression = "(+)";

    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        message = e.message;
    }
    EXPECT_EQ(message, "Invalid number of arguments for function \"+\", Expected at least 1, got 0");
}

TEST(add_test, ShouldThrowAnErrorWhenInvalidArgumentIsPasseg) {
    const auto expression = "(+ 10 \"Hello World\")";

    bool errorIsThrown = false;
    std::string message;
    try {
        run_program(expression);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }
    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid argument type for function \"+\", Expected number, got string");
}
