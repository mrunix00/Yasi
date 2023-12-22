#include "utils/break_lines.h"
#include <gtest/gtest.h>

TEST(break_lines, ShouldReturnSameInputIfOnlyOneLineIsGiven) {
    auto input = "(+ 1 2)";

    std::vector<std::string> expected_result = {"(+ 1 2)"};
    auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(break_lines, ShouldBreakTwoExpressions) {
    auto input = "(define x)(print x)";

    std::vector<std::string> expected_result = {"(define x)", "(print x)"};
    auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(break_lines, ShouldBreakTwoNestedExpressions) {
    auto input = "(define x (+ 1 2))(print x)";

    std::vector<std::string> expected_result = {"(define x (+ 1 2))", "(print x)"};
    auto actual_result = break_lines(input);

    EXPECT_EQ(expected_result == actual_result, true);
}
