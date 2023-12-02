#include "builtin_functions/subtract/subtract.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(add_test, ShouldSubtractNumbers) {
    auto expression = {SyntaxTreeNode(Token(Token::Integer, "5")),
                       SyntaxTreeNode(Token(Token::Integer, "2"))};

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "3"));
    auto actual = Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedSubtraction) {
    auto expression = {
            SyntaxTreeNode(Token(Token::Integer, "9")),
            SyntaxTreeNode(Token(Token::Integer, "-"),
                           {SyntaxTreeNode(Token(Token::Integer, "3")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))})};

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "8"));
    auto actual = Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ThrowExceptionOnInvalidArgumentsInSubtraction) {
    bool isCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;

    const std::vector<SyntaxTreeNode> expression = {
            SyntaxTreeNode(Token(Token::Integer, "1")),
            SyntaxTreeNode(Token(Token::String, "\"Hello World\"", 2, 3)),
    };

    try {
        Subtract().evaluate(expression);
    } catch (SyntaxError &error) {
        isCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(isCaught, true);
    EXPECT_EQ(errorMessage == "\"Hello World\" is not a number", true);
    EXPECT_EQ(line == expression[1].token.line, true);
    EXPECT_EQ(column == expression[1].token.column, true);
}
