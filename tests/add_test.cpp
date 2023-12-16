#include "exceptions/SyntaxError.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/builtin_functions/add/Add.h"
#include <gtest/gtest.h>

TEST(add_test, ShouldAddTwoNumbers) {
    // (+ 1 2)
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "3"));
    auto actual = *RecursiveEvaluation::Add().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ShouldAddDecimalNumbers) {
    // (+ 1.2 2)
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Decimal, "1.2")),
            new SyntaxTreeNode(new Token(Token::Integer, "2")),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Decimal, "3.2"));
    auto actual = *RecursiveEvaluation::Add().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}


TEST(add_test, ShouldEvaluateNestedAddition) {
    // (+ 1 (+ 2 3))
    auto expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(
                    new Token(Token::Symbol, "+"),
                    {
                            new SyntaxTreeNode(new Token(Token::Integer, "2")),
                            new SyntaxTreeNode(new Token(Token::Integer, "3")),
                    }),
    };

    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "6"));
    auto actual = *RecursiveEvaluation::Add().evaluate(expression);

    EXPECT_EQ(expectedResult == actual, true);
}

TEST(add_test, ThrowExceptionOnInvalidArguments) {
    bool isCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;

    const std::vector<SyntaxTreeNode *> expression = {
            new SyntaxTreeNode(new Token(Token::Integer, "1")),
            new SyntaxTreeNode(new Token(Token::String, "\"Hello World\"", 2, 3)),
    };

    try {
        RecursiveEvaluation::Add().evaluate(expression);
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

TEST(add_test, ShouldReturnZeroWhenNoArgumentsAreFound) {
    auto expectedResult = SyntaxTreeNode(new Token(Token::Integer, "0"));
    auto actualResult = *RecursiveEvaluation::Add().evaluate({});
    EXPECT_EQ(actualResult == expectedResult, true);
}
