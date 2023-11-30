#include "builtin_functions/divide/Divide.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(add_test, ShouldDivideNumbers) {
    auto expression = {SyntaxTreeNode(Token(Token::Integer, "8")),
                       SyntaxTreeNode(Token(Token::Integer, "2"))};

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "4"));
    auto actual = Divide().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedDivision) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "18")),
            SyntaxTreeNode(Token(Token::Integer, "/"),
                           {SyntaxTreeNode(Token(Token::Integer, "4")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))})};

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "9"));
    auto actual = Divide().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}