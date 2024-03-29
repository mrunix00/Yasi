#include "boilerplate.h"
#include "exceptions/SyntaxError.h"

TEST(variables_test, ShouldAssignAValueToAVariable) {
    const auto program =
            "(define x 10)"
            "(+ x 10)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(variables_test, ShouldAssignTwoValuesToTwoVariablesAndSumThem) {
    const auto program =
            "(define x 10)"
            "(define y 20)"
            "(+ x y)";

    const auto expected_result = StackObject((double) 30);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(variables_test, ShouldDefineAVariableWithAnExpression) {
    const auto program =
            "(define x (+ 10 20))"
            "(+ x 10)";

    const auto expected_result = StackObject((double) 40);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(variables_test, ShouldDisplayAVariableValueWhenCalled) {
    const auto program =
            "(define x 10)"
            "x";

    const auto expected_result = StackObject((double) 10);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(variables_test, ShouldDisplayALiteralWhenItsCalled) {
    const auto program = "10";

    const auto expected_result = StackObject((double) 10);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(variables_test, ShouldThrowAnErrorOnUndefinedVariable) {
    const auto program = "(+ x 10)";

    bool errorIsThrown = false;
    std::string errorMessage;

    try {
        run_program(program);
    } catch (const SyntaxError &e) {
        errorIsThrown = true;
        errorMessage = e.message;
    }

    EXPECT_TRUE(errorIsThrown);
    EXPECT_EQ(errorMessage, "Undefined variable -> x");
}
