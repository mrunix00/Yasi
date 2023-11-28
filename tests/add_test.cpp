#include <gtest/gtest.h>
#include "parser/SyntaxTreeNode.h"
#include "builtin_functions/add/add.h"

TEST(add_test, ShouldAddTwoNumbers) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "1")),
            SyntaxTreeNode(Token(Token::Integer, "2"))
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "3"));
    auto actual = Add().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedAddition) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "1")),
            SyntaxTreeNode(
                    Token(Token::Integer, "+"),
                    {
                            SyntaxTreeNode(Token(Token::Integer, "2")),
                            SyntaxTreeNode(Token(Token::Integer, "3"))
                    }
            )
    };

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "6"));
    auto actual = Add().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}