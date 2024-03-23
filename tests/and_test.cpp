#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(and_test, ShouldReturnTrueWhenBothAreTrue) {
    const auto program = "(and (= 1 1) (= 3 3))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldReturnFalseWhenFirstIsFalse) {
    const auto program = "(and (= 1 2) (= 3 3))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldReturnFalseWhenSecondIsFalse) {
    const auto program = "(and (= 1 1) (= 3 4))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldReturnFalseWhenBothAreFalse) {
    const auto program = "(and (= 1 2) (= 3 4))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldReturnFalseWhenOneOfThreeArgumentsIsFalse) {
    const auto program = "(and (= 1 1) (= 3 4) (= 5 6))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldReturnTrueWhenAllThreeArgumentsAreTrue) {
    const auto program = "(and (= 1 1) (= 3 3) (= 5 5))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(and_test, ShouldThrowErrorWhenNoArguments) {
    const auto program = "(and)";

    bool error_is_thrown = false;
    std::string message;
    try {
        run_program(program);
    } catch (const SyntaxError& e) {
        error_is_thrown = true;
        message = e.message;
    }

    EXPECT_TRUE(error_is_thrown);
    EXPECT_EQ(message, "Invalid number of arguments for function \"and\", Expected at least 1, got 0");
}