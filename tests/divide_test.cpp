#include "evaluation/builtin_functions/divide/Divide.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(divide_test, ShouldDivideNumbers) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "8")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "4"));
    auto actual = *Divide().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(divide_test, ShouldEvaluateNestedDivision) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "18")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "/"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "4")),
                            new SyntaxTreeNode(new Token(Token::Integer, "2")),
                    }),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "9"));
    auto actual = *Divide().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(divide_test, ThrowExceptionOnDivisionWithInvalidArguments) {
    bool isCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;

    const std::vector<SyntaxTreeNode *> expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::String, "\"Hello World\"", 2, 3)),
    };

    try {
        Divide().evaluate(expression);
    } catch (SyntaxError &error) {
        isCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(isCaught, true);
    EXPECT_EQ(errorMessage == "\"Hello World\" is not a number", true);
    EXPECT_EQ(line == expression[1]->token->line, true);
    EXPECT_EQ(column == expression[1]->token->column, true);
}

TEST(divide_test, ThrowExceptionOnZeroArguments) {
    bool isCaught = false;
    std::string errorMessage;

    try {
        Divide().evaluate({});
    } catch (SyntaxError &error) {
        isCaught = true;
        errorMessage = error.message;
    }

    EXPECT_EQ(isCaught, true);
    EXPECT_EQ(errorMessage == "At least 1 argument was expected but none were found", true);
}

TEST(divide_test, ThrowExceptionOnDivisionByZero) {
    bool isCaught = false;
    std::string errorMessage;
    int line, column;

    try {
        Divide().evaluate({
                new SyntaxTreeNode(new Token(Token::Integer, "1")),
                new SyntaxTreeNode(new Token(Token::Integer, "0", 6, 9)),
        });
    } catch (SyntaxError &error) {
        isCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(isCaught, true);
    EXPECT_EQ(errorMessage == "Division by zero", true);
    EXPECT_EQ(line == 6, true);
    EXPECT_EQ(column == 9, true);
}
