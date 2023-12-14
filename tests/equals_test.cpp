#include "evaluation/builtin_functions/equals/Equals.h"
#include "lexer/Lexer.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(equals_test, ShouldReturnTrueIfEquals) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#t"));
    auto actual_result = Equals().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "10")),
            SyntaxTreeNode(Token(Token::Integer, "10")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(equals_test, ShouldReturnFalseIfNotEquals) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#f"));
    auto actual_result = Equals().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "30")),
            SyntaxTreeNode(Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(equals_test, CompareMoreThanTwoArguments) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#f"));
    auto actual_result = Equals().evaluate({
            SyntaxTreeNode(Token(Token::Integer, "10")),
            SyntaxTreeNode(Token(Token::Integer, "10")),
            SyntaxTreeNode(Token(Token::Integer, "5")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(equals_test, CompareIntegersAndDecimals) {
    auto expected_result = SyntaxTreeNode(Token(Token::Boolean, "#t"));
    auto actual_result = Equals().evaluate({
            SyntaxTreeNode(Token(Token::Decimal, "30.0")),
            SyntaxTreeNode(Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

