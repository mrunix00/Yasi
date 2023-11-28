#include <gtest/gtest.h>
#include "parser/SyntaxTreeNode.h"
#include "builtin_functions/subtract/subtract.h"

TEST(add_test, ShouldSubtractNumbers) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "5")),
            SyntaxTreeNode(Token(Token::Integer, "2"))
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "3"));
    auto actual = Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedSubtraction) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "9")),
            SyntaxTreeNode(
                    Token(Token::Integer, "-"),
                    {
                            SyntaxTreeNode(Token(Token::Integer, "3")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))
                    }
            )
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "8"));
    auto actual = Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}