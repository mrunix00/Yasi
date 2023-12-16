#include "recursive_evaluation/builtin_functions/greater_than/GreaterThan.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(greater_than_test, ShouldReturnTrueIfGreater) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *GreaterThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, ShouldReturnFalseIfNotGreater) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *GreaterThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, CompareMoreThanTwoArguments) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *GreaterThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(greater_than_test, CompareIntegersAndDecimals) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *GreaterThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Decimal, "30.5")),
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}
