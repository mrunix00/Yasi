#include "boilerplate.h"

TEST(vm_cond_test, ShouldNotJumpOnTrueCondition) {
    const auto program = "(cond (> 20 10) 20)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_cond_test, ShouldJumpOnFalseCondition) {
    const auto program = "(cond (> 10 20) 10)";

    const auto expected_result = StackObject();
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(vm_conf_test, ShouldJumpToOppositeCondition) {
    const auto program = "(cond (> 20 10) 20 10)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}
