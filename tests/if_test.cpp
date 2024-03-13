#include "boilerplate.h"

TEST(if_test, ShouldNotJumpOnTrueCondition) {
    const auto program = "(if (> 20 10) 20)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(if_test, ShouldJumpOnFalseCondition) {
    const auto program = "(if (> 10 20) 10)";

    const auto expected_result = StackObject();
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(if_test, ShouldJumpToOppositeCondition) {
    const auto program = "(if (> 20 10) 20 10)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
