#include "utils/break_lines.h"
#include <gtest/gtest.h>

TEST(break_lines, ShouldReturnSameInputIfOnlyOneLineIsGiven) {
    const auto input = "(+ 1 2)";

    const std::vector<std::string> expected_result = {"(+ 1 2)"};
    const auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(break_lines, ShouldBreakTwoExpressions) {
    const auto input = "(define x)(print x)";

    const std::vector<std::string> expected_result = {"(define x)", "(print x)"};
    const auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(break_lines, ShouldBreakTwoNestedExpressions) {
    const auto input = "(define x (+ 1 2))(print x)";

    const std::vector<std::string> expected_result = {
            "(define x (+ 1 2))",
            "(print x)",
    };
    const auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}
