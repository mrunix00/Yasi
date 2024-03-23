#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(or_test, ShouldReturnFalseWhenBothAreFalse) {
    const auto program = "(or (= 1 2) (= 3 4))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldReturnTrueWhenFirstIsTrue) {
    const auto program = "(or (= 1 1) (= 3 4))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldReturnTrueWhenSecondIsTrue) {
    const auto program = "(or (= 1 2) (= 3 3))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldReturnTrueWhenBothAreTrue) {
    const auto program = "(or (= 1 1) (= 3 3))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldReturnTrueWhenOneOfThreeArgumentsIsTrue) {
    const auto program = "(or (= 1 2) (= 3 4) (= 5 5))";

    const auto expected = StackObject(true);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldReturnFalseWhenAllThreeArgumentsAreFalse) {
    const auto program = "(or (= 1 2) (= 3 4) (= 5 6))";

    const auto expected = StackObject(false);
    const auto actual = run_program(program);

    EXPECT_EQ(expected, actual);
}

TEST(or_test, ShouldThrowErrorWhenNoArguments) {
    const auto program = "(or)";

    bool error_is_thrown = false;
    std::string message;
    try {
        run_program(program);
    } catch (const SyntaxError &error) {
        error_is_thrown = true;
        message = error.message;
    }

    EXPECT_TRUE(error_is_thrown);
    EXPECT_EQ("Invalid number of arguments for function \"or\", Expected at least 1, got 0", message);
}