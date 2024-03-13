#include "boilerplate.h"

TEST(cond_test, ShouldNotJumpOnTrueCondition) {
    const auto program = "(cond (> 20 10) 20)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(cond_test, ShouldJumpOnFalseCondition) {
    const auto program = "(cond (> 10 20) 10)";

    const auto expected_result = StackObject();
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(cond_test, ShouldJumpToOppositeCondition) {
    const auto program = "(cond (> 20 10) 20 10)";

    const auto expected_result = StackObject((double) 20);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(cond_test, ShouldTestMultipleCases) {
    const auto program = "(cond (= 20 10) 20 (= 10 10) 10)";

    const auto expected_result = StackObject((double) 10);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(cond_test, ShouldFallbackToDefaultCase) {
    const auto program = "(cond (= 20 5) 20 (= 10 5) 10 5)";

    const auto expected_result = StackObject((double) 5);
    const auto actual_result = run_program(program);

    EXPECT_EQ(actual_result, expected_result);
}