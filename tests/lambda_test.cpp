#include "boilerplate.h"

TEST(lambda_test, ShouldDefineALambdaFunctionAndCallIt) {
    const auto expression =
            "(define add (lambda (a b) (+ a b)))\n"
            "(add 5 6)";

    const auto expected_result = StackObject((double) 11);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(lambda_test, ShouldDefineALambdaWithLambdaSymbol) {
    const auto expression =
            "(define add (λ (a b) (+ a b)))\n"
            "(add 5 6)";

    const auto expected_result = StackObject((double) 11);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(lambda_test, ShouldPassLambdaAsArgument) {
    const auto expression =
            "(define add (lambda (a b) (+ a b)))\n"
            "(define (calc f a b) (f a b))\n"
            "(calc add 5 6)";

    const auto expected_result = StackObject((double) 11);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}
