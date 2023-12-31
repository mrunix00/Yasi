#include "lexer/Lexer.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/builtin_functions/equals/Equals.h"
#include <gtest/gtest.h>

TEST(recursive_evaluation_equals_test, ShouldReturnTrueIfEquals) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *RecursiveEvaluation::Equals().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(recursive_evaluation_equals_test, ShouldReturnFalseIfNotEquals) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *RecursiveEvaluation::Equals().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
            new SyntaxTreeNode(new Token(Token::Integer, "20")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(recursive_evaluation_equals_test, CompareMoreThanTwoArguments) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#f"));
    auto actual_result = *RecursiveEvaluation::Equals().evaluate({
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "10")),
            new SyntaxTreeNode(new Token(Token::Integer, "5")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}

TEST(recursive_evaluation_equals_test, CompareIntegersAndDecimals) {
    auto expected_result = SyntaxTreeNode(new Token(Token::Boolean, "#t"));
    auto actual_result = *RecursiveEvaluation::Equals().evaluate({
            new SyntaxTreeNode(new Token(Token::Decimal, "30.0")),
            new SyntaxTreeNode(new Token(Token::Integer, "30")),
    });
    EXPECT_EQ(expected_result == actual_result, true);
}
