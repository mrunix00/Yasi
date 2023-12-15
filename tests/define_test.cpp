#include "evaluation/builtin_functions/define/Define.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(define_test, ShouldDefineAVariable) {
    Define().evaluate({
            new SyntaxTreeNode(new Token(Token::Symbol, "x")),
            new SyntaxTreeNode(new Token(Token::Integer, "15")),
    });

    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "5")),
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
            });
    auto expected_result = SyntaxTreeNode(new Token(Token::Integer, "20"));
    auto actual_result = *Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldDefineAVariableWithAnExpression) {
    Define().evaluate({
            new SyntaxTreeNode(new Token(Token::Symbol, "x")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "+"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "1")),
                            new SyntaxTreeNode(new Token(Token::Integer, "2")),
                    }),
    });

    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "5")),
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
            });
    auto expected_result = SyntaxTreeNode(new Token(Token::Integer, "8"));
    auto actual_result = *Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldDefineASimpleFunction) {
    Define().evaluate({
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "square"),
                    {
                            new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    }),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "*"),
                    {
                            new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    }),
    });

    auto expression = new SyntaxTreeNode(
            new Token(Token::Symbol, "square"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "10")),
            });

    auto expected_result = SyntaxTreeNode(new Token(Token::Integer, "100"));
    auto actual_result = *Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldHaveScopedFunctionArguments) {
    Define().evaluate({
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "square"),
                    {
                            new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                    }),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "*"),
                    {
                            new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                    }),
    });

    Evaluate::evaluate(
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "square"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "20")),
                    }));

    bool isCaught = false;
    try {
        Evaluate::evaluate(new SyntaxTreeNode(new Token(Token::Symbol, "y")));
    } catch (SyntaxError &error) {
        isCaught = true;
    }
    EXPECT_EQ(isCaught, true);
}
