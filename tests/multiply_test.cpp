#include <gtest/gtest.h>
#include "parser/SyntaxTreeNode.h"
#include "builtin_functions/multiply/multiply.h"

TEST(add_test, ShouldMultiplyNumbers) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "2")),
            SyntaxTreeNode(Token(Token::Integer, "2"))
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "4"));
    auto actual = Multiply().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedMultiplication) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "2")),
            SyntaxTreeNode(
                    Token(Token::Integer, "*"),
                    {
                            SyntaxTreeNode(Token(Token::Integer, "3")),
                            SyntaxTreeNode(Token(Token::Integer, "3"))
                    }
            )
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "18"));
    auto actual = Multiply().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}