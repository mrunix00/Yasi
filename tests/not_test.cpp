#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(not_test, ShouldNegateATrueCondition) {
    const auto program = "(not (= 10 10))";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(not_test, ShouldNegateAFalseCondition) {
    const auto program = "(not (= 20 10))";

    const auto expected_result = StackObject(true);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(not_test, ShouldThrowAnErrorWhenNoArgsWereFound) {
    const auto program = "(not)";

    bool errorIsThrown = false;
    std::string message;

    try {
        run_program(program);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid number of arguments for function \"not\", Expected 1, got 0");
}

TEST(not_test, ShouldThrowAnErrorWhenMoreThanOneArgIsGiven) {
    const auto program = "(not (= 10 10) (= 20 20))";

    bool errorIsThrown = false;
    std::string message;

    try {
        run_program(program);
    } catch (const SyntaxError& e) {
        errorIsThrown = true;
        message = e.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(message, "Invalid number of arguments for function \"not\", Expected 1, got 2");
}

TEST(not_test, ShouldReturnFalseWhenGivenNonBoolean) {
    const auto program = "(not 10)";

    const auto expected_result = StackObject(false);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
