#include "boilerplate.h"

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
