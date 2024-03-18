#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(calls_test, function_with_a_single_arg) {
    const auto program =
            "(define (square x) (* x x))\n"
            "(square 10)";

    const auto expected_result = StackObject((double) 100);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(calls_test, function_with_multiple_args) {
    const auto program =
            "(define (subtract x y) (- x y))\n"
            "(subtract 50 10)";

    const auto expected_result = StackObject((double) 40);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(calls_test, ThrowErrorOnUndefinedFunction) {
    const auto program = "(subtract 50 10)";

    bool errorIsThrown = false;
    std::string errorMessage;
    try {
        run_program(program);
    } catch (SyntaxError &error) {
        errorIsThrown = true;
        errorMessage = error.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(errorMessage, "Undefined function -> subtract");
}

TEST(calls_test, ThrowAnErrorOnInvalidNumberOfArguments) {
    const auto program =
            "(define (subtract x y) (- x y))(subtract 50)";

    bool errorIsThrown = false;
    std::string errorMessage;
    try {
        run_program(program);
    } catch (SyntaxError &error) {
        errorIsThrown = true;
        errorMessage = error.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(errorMessage, "Invalid number of arguments for function \"subtract\", "
                            "Expected 2, got 1");
}