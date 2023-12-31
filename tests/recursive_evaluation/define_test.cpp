#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/builtin_functions/define/Define.h"
#include <gtest/gtest.h>

TEST(recursive_evaluation_define_test, ShouldDefineAVariable) {
    RecursiveEvaluation::Define().evaluate({
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
    auto actual_result = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(recursive_evaluation_define_test, ShouldDefineAVariableWithAnExpression) {
    RecursiveEvaluation::Define().evaluate({
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
    auto actual_result = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(recursive_evaluation_define_test, ShouldDefineASimpleFunction) {
    RecursiveEvaluation::Define().evaluate({
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
    auto actual_result = *RecursiveEvaluation::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}

TEST(recursive_evaluation_define_test, ShouldHaveScopedFunctionArguments) {
    RecursiveEvaluation::Define().evaluate({
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

    RecursiveEvaluation::evaluate(
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "square"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "20")),
                    }));

    bool isCaught = false;
    try {
        RecursiveEvaluation::evaluate(new SyntaxTreeNode(new Token(Token::Symbol, "y")));
    } catch (SyntaxError &error) {
        isCaught = true;
    }
    EXPECT_EQ(isCaught, true);
}
