#include "builtin_functions/greater_than/greater_than.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(greater_than_test, ShouldReturnTrueIfGreater) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#t"));
    auto actual_result = GreaterThan().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "20")),
            SyntaxTreeNode(Token(Token::Integer, "10")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, ShouldReturnFalseIfNotGreater) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#f"));
    auto actual_result = GreaterThan().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "10")),
            SyntaxTreeNode(Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, CompareMoreThanTwoArguments) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#f"));
    auto actual_result = GreaterThan().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "30")),
            SyntaxTreeNode(Token(Token::Integer, "20")),
            SyntaxTreeNode(Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, CompareIntegersAndDecimals) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#t"));
    auto actual_result = GreaterThan().evaluate({
            SyntaxTreeNode(Token(Token::Decimal, "30.5")),
            SyntaxTreeNode(Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

