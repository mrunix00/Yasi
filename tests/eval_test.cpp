#include "../src/parser/SyntaxTreeNode.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "recursive_evaluation/RecursiveEvaluation.h"
#include <gtest/gtest.h>

TEST(eval_test, ShouldEvaluateSimpleSumExpression) {
    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "3"));
    auto actualResult = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleMultiplication) {
    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "3")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "6"));
    auto actualResult = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleSubtraction) {
    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "-"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "70")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "68"));
    auto actualResult = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateNestedExpression) {
    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "-"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Integer, "32")),
                                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
                            }),
                    new SyntaxTreeNode(new Token(Token::Integer, "7")),
            });

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "37"));
    auto actualResult = *RecursiveEvaluation::evaluate(expression);
    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldCallFunctionWithNoArguments) {
    auto expression = new SyntaxTreeNode(new Token(Token::Symbol, "+"));

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "0"));
    auto actualResult = *RecursiveEvaluation::evaluate(expression);
    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldThrowExceptionWhenTheExpressionIsInvalid) {
    int line, column;
    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "+", 1, 2),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1", 1, 4)),
                    new SyntaxTreeNode(new Token(Token::String, "\"Hello\"", 1, 6)),
            });
    try {
        RecursiveEvaluation::evaluate(expression);
    } catch (SyntaxError &error) {
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(line == expression->children[1]->token->line, true);
    EXPECT_EQ(column == expression->children[1]->token->column, true);
}

TEST(eval_test, ShouldThrowExceptionWhenErrorLocationIsNotFoundInArguments) {
    int line, column;
    auto expression = new SyntaxTreeNode(new Token(Token::Symbol, "/", 1, 2));
    try {
        RecursiveEvaluation::evaluate(expression);
    } catch (SyntaxError &error) {
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(line == expression->token->line, true);
    EXPECT_EQ(column == expression->token->column, true);
}
