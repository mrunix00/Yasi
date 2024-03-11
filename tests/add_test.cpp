#include "boilerplate.h"

TEST(vm_add_test, ShouldAddTwoLiterals) {
    const auto expression = "(+ 10 20)";

    const auto expected_result = StackObject((double) 30);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_add_test, ShouldAddTwoDecimalNumbers) {
    const auto expression = "(+ 3.1415 1.5)";

    const auto expected_result = StackObject(4.6415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_add_test, ShouldAddDecimalAndIntegerNumbers) {
    const auto expression = "(+ 3.1415 1)";

    const auto expected_result = StackObject((double) 4.1415);
    const auto actual_result = run_program(expression);

    EXPECT_EQ(actual_result, expected_result);
}
