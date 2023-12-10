#include "builtin_functions/define/define.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(define_test, ShouldDefineAVariable) {
    Define().evaluate({SyntaxTreeNode(Token(Token::Symbol, "x")),
                       SyntaxTreeNode(Token(Token::Integer, "15"))});

    auto expression = SyntaxTreeNode(Token(Token::Symbol, "+"),
                                     {
                                             SyntaxTreeNode(Token(Token::Integer, "5")),
                                             SyntaxTreeNode(Token(Token::Symbol, "x")),
                                     });
    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "20"));
    auto actual_result = Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldDefineAVariableWithAnExpression) {
    Define().evaluate({
            SyntaxTreeNode(Token(Token::Symbol, "x")),
            SyntaxTreeNode(Token(Token::Symbol, "+"),
                           {
                                   SyntaxTreeNode(Token(Token::Integer, "1")),
                                   SyntaxTreeNode(Token(Token::Integer, "2")),
                           }),
    });

    auto expression = SyntaxTreeNode(Token(Token::Symbol, "+"),
                                     {
                                             SyntaxTreeNode(Token(Token::Integer, "5")),
                                             SyntaxTreeNode(Token(Token::Symbol, "x")),
                                     });
    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "8"));
    auto actual_result = Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldDefineASimpleFunction) {
    Define().evaluate({
            SyntaxTreeNode(
                    Token(Token::Symbol, "square"),
                    {
                            SyntaxTreeNode(Token(Token::Symbol, "x")),
                    }),
            SyntaxTreeNode(
                    Token(Token::Symbol, "*"),
                    {
                            Token(Token::Symbol, "x"),
                            Token(Token::Symbol, "x"),
                    }),
    });

    auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "square"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "10")),
            });

    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "100"));

    auto actual_result = Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(define_test, ShouldHaveScopedFunctionArguments) {
    Define().evaluate({
            SyntaxTreeNode(
                    Token(Token::Symbol, "square"),
                    {
                            SyntaxTreeNode(Token(Token::Symbol, "y")),
                    }),
            SyntaxTreeNode(
                    Token(Token::Symbol, "*"),
                    {
                            Token(Token::Symbol, "y"),
                            Token(Token::Symbol, "y"),
                    }),
    });

    Evaluate::evaluate(SyntaxTreeNode(
            Token(Token::Symbol, "square"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "20")),
            }));

    bool isCaught = false;
    try {
        Evaluate::evaluate(SyntaxTreeNode(Token(Token::Symbol, "y")));
    } catch (SyntaxError &error) {
        isCaught = true;
    }
    EXPECT_EQ(isCaught, true);
}
