#include "boilerplate.h"

TEST(vm_calls_test, function_with_a_single_arg) {
    const auto program =
            "(define (square x) (* x x))\n"
            "(square 10)";

    const auto expected_result = StackObject((double) 100);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_calls_test, function_with_multiple_args) {
    const auto program =
            "(define (subtract x y) (- x y))\n"
            "(subtract 50 10)";

    const auto expected_result = StackObject((double) 40);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}