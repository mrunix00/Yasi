#include "recursive_evaluation/builtin_functions/subtract/Subtract.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(subtract_test, ShouldSubtractNumbers) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "5")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "3"));
    auto actual = *Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(subtract_test, ShouldSubtractDecimalNumbers) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Decimal, "5.2")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token((float) 3.2));
    auto actual = *Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}


TEST(subtract_test, ShouldEvaluateNestedSubtraction) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "9")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "-"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "3")),
                            new SyntaxTreeNode(new Token(Token::Integer, "2")),
                    }),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "8"));
    auto actual = *Subtract().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(subtract_test, ThrowExceptionOnInvalidArgumentsInSubtraction) {
    bool isCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;

    const std::vector<SyntaxTreeNode *> expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::String, "\"Hello World\"", 2, 3)),
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
    EXPECT_EQ(line == expression[1]->token->line, true);
    EXPECT_EQ(column == expression[1]->token->column, true);
}

TEST(subtract_test, ThrowExceptionOnZeroArguments) {
    bool isCaught = false;
    std::string errorMessage;

    try {
        Subtract().evaluate({});
    } catch (SyntaxError &error) {
        isCaught = true;
        errorMessage = error.message;
    }

    EXPECT_EQ(isCaught, true);
    EXPECT_EQ(errorMessage == "At least 1 argument was expected but none were found", true);
}
