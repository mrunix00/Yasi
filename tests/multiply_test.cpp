#include "recursive_evaluation/builtin_functions/multiply/Multiply.h"
#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(multiply_test, ShouldMultiplyNumbers) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "4"));
    auto actual = *Multiply().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldEvaluateNestedMultiplication) {
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "*"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "3")),
                            new SyntaxTreeNode(new Token(Token::Integer, "3")),
                    }),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "18"));
    auto actual = *Multiply().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(multiply_test, ShouldMultiplyDecimalNumbers) {
    // (* 1.2 2)
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Decimal, "1.2")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Decimal, "2.4"));
    auto actual = *Multiply().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(multiply_test, ThrowExceptionOnMultiplyWithInvalidArguments) {
    bool isCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;

    const std::vector<SyntaxTreeNode *> expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::String, "\"Hello World\"", 2, 3)),
    };

    try {
        Multiply().evaluate(expression);
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

TEST(multiply_test, ShouldReturnZeroWhenNoArgumentsAreFound) {
    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "1"));
    auto actualResult = *Multiply().evaluate({});
    EXPECT_EQ(actualResult == expectedResult, true);
}
