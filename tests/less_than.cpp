#include "evaluation/builtin_functions/less_than/LessThan.h"
#include "lexer/Lexer.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(less_than_test, ShouldReturnTrueIfNotGreater) {
    auto expected_result =  SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *LessThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(less_than_test, ShouldReturnFalseIfGreater) {
    auto expected_result =  SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *LessThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(less_than_test, CompareMoreThanTwoArguments) {
    auto expected_result =  SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *LessThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
            new SyntaxTreeNode(new Token(Token::Integer, "5")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(less_than_test, CompareIntegersAndDecimals) {
    auto expected_result =  SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *LessThan().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
            new SyntaxTreeNode(new Token(Token::Decimal, "30.5")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

