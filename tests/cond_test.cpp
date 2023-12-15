#include "evaluation/builtin_functions/cond/Cond.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(cond_test, ShouldEvaluateExpressionIfConditionIsMet) {
    auto condition = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
            });
    auto result = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });

    auto expected_result = SyntaxTreeNode(new Token(Token::Integer, "3"));
    auto actual_result = *Cond().evaluate({condition, result});

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldNotEvaluateExpressionIfConditionIsNotMet) {
    auto condition = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "0")),
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
            });
    auto result = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });

    auto expected_result = SyntaxTreeNode();
    auto actual_result = *Cond().evaluate({condition, result});

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldEvaluateMultipleConditions) {
    auto condition1 = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "0")),
            });
    auto result1 = new SyntaxTreeNode(new Token(Token::Integer, "0"));

    auto condition2 = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
            });
    auto result2 = new SyntaxTreeNode(new Token(Token::Integer, "1"));

    auto expected_result = SyntaxTreeNode(new Token(Token::Integer, "1"));
    auto actual_result = *Cond().evaluate({
            condition1,
            result1,
            condition2,
            result2,
    });

    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(cond_test, ShouldEvaluateDefaultResultIfNoConditionsAreMet) {
    auto condition1 = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "0")),
            });
    auto result1 = new SyntaxTreeNode(new Token(Token::Integer, "0"));

    auto condition2 = new SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "0")),
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
            });
    auto result2 = new SyntaxTreeNode(new Token(Token::Integer, "1"));

    auto default_result = SyntaxTreeNode(new Token(Token::Integer, "2"));

    auto actual_result = *Cond().evaluate({
            condition1,
            result1,
            condition2,
            result2,
            &default_result,
    });

    EXPECT_EQ(actual_result == default_result, true);
}
