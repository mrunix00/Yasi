#include "builtin_functions/cond/cond.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(cond_test, ShouldEvaluateExpressionIfConditionIsMet) {
    auto condition = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "1")),
            });
    auto result = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "2")),
            });

    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "3"));
    auto actual_result = Cond().evaluate({condition, result});

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldNotEvaluateExpressionIfConditionIsNotMet) {
    auto condition = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "0")),
                    SyntaxTreeNode(Token(Token::Integer, "1")),
            });
    auto result = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "2")),
            });

    auto expected_result = SyntaxTreeNode();
    auto actual_result = Cond().evaluate({condition, result});

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldEvaluateMultipleConditions) {
    auto condition1 = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "0")),
            });
    auto result1 = SyntaxTreeNode(Token(Token::Integer, "0"));

    auto condition2 = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "1")),
            });
    auto result2 = SyntaxTreeNode(Token(Token::Integer, "1"));

    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "1"));
    auto actual_result = Cond().evaluate({
            condition1,
            result1,
            condition2,
            result2,
    });

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldEvaluateDefaultResultIfNoConditionsAreMet) {
    auto condition1 = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "0")),
            });
    auto result1 = SyntaxTreeNode(Token(Token::Integer, "0"));

    auto condition2 = SyntaxTreeNode(
            Token(Token::Symbol, "="),
            {
                    SyntaxTreeNode(Token(Token::Integer, "0")),
                    SyntaxTreeNode(Token(Token::Integer, "1")),
            });
    auto result2 = SyntaxTreeNode(Token(Token::Integer, "1"));

    auto default_result = SyntaxTreeNode(Token(Token::Integer, "2"));

    auto expected_result = default_result;
    auto actual_result = Cond().evaluate({
            condition1,
            result1,
            condition2,
            result2,
            default_result,
    });

    EXPECT_EQ(expected_result == actual_result, true);
}
