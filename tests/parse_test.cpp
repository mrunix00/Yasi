#include "../src/parser/Parser.h"
#include "exceptions/SyntaxError.h"
#include <gtest/gtest.h>

TEST(parse_test, ParseSimpleOperation) {
    // ( + 1 2 )
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
    };
    auto expected =
            SyntaxTreeNode(Token(Token::Symbol, "+"),
                           {SyntaxTreeNode(Token(Token::Integer, "1")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))});

    auto actual = Parser::parse(sample);

    EXPECT_EQ(actual == expected, true);
}

TEST(parse_test, ParseSimpleOperationWithStringArgument) {
    // ( print "Hello World )
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "print"),
            Token(Token::String, "\"Hello World\""),
            Token(Token::ClosedBracket, ")"),
    };
    auto expected = SyntaxTreeNode(
            Token(Token::Symbol, "print"),
            {
                    SyntaxTreeNode(Token(Token::String, "\"Hello World\"")),
            });

    auto actual = Parser::parse(sample);

    EXPECT_EQ(actual == expected, true);
}

TEST(parse_test, ParseNestedOperation) {
    // ( + ( + 1 3 ) 2 )
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "3"),
            Token(Token::ClosedBracket, ")"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
    };

    auto expected = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {SyntaxTreeNode(Token(Token::Symbol, "+"),
                            {SyntaxTreeNode(Token(Token::Integer, "1")),
                             SyntaxTreeNode(Token(Token::Integer, "3"))}),
             SyntaxTreeNode(Token(Token::Integer, "2"))});

    auto actual = Parser::parse(sample);

    EXPECT_EQ(actual == expected, true);
}

TEST(parse_test, ParseDeeplyNestedOperation) {
    // ( + ( * 2 3 ) ( + ( * 1 2 ) 4 ) 7 )
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "*"),
            Token(Token::Integer, "2"),
            Token(Token::Integer, "3"),
            Token(Token::ClosedBracket, ")"),
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "*"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
            Token(Token::Integer, "4"),
            Token(Token::ClosedBracket, ")"),
            Token(Token::Integer, "7"),
            Token(Token::ClosedBracket, ")"),
    };

    auto expected = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    SyntaxTreeNode(Token(Token::Symbol, "*"),
                                   {SyntaxTreeNode(Token(Token::Integer, "2")),
                                    SyntaxTreeNode(Token(Token::Integer, "3"))}),
                    SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {SyntaxTreeNode(Token(Token::Symbol, "*"),
                                            {SyntaxTreeNode(Token(Token::Integer, "1")),
                                             SyntaxTreeNode(Token(Token::Integer, "2"))}),
                             SyntaxTreeNode(Token(Token::Integer, "4"))}),
                    SyntaxTreeNode(Token(Token::Integer, "7")),
            });

    auto actual = Parser::parse(sample);

    EXPECT_EQ(actual == expected, true);
}

TEST(parse_test, ShouldThrowExceptionsOnExtraParenthesis) {
    auto exceptionCaught = false;
    auto expectedErrorMessage = "Unexpected parenthesis -> ')'";
    std::string actualErrorMessage;
    int extraParenthesisLine;
    int extraParenthesisColumn;

    // (+ 1 2 ))
    const std::vector<Token> sample = {
            Token(Token::OpenBracket, "(", 1, 1),
            Token(Token::Symbol, "+", 1, 2),
            Token(Token::Integer, "1", 1, 4),
            Token(Token::Integer, "2", 1, 6),
            Token(Token::ClosedBracket, ")", 1, 8),
            Token(Token::ClosedBracket, ")", 1, 9)};

    try {
        Parser::parse(sample);
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        actualErrorMessage = error.message;
        extraParenthesisLine = error.line;
        extraParenthesisColumn = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(expectedErrorMessage == actualErrorMessage, true);
    EXPECT_EQ(extraParenthesisLine == sample[5].line, true);
    EXPECT_EQ(extraParenthesisColumn == sample[5].column, true);
}

TEST(parse_test, ShouldThrowExceptionsOnMissingOperator) {
    bool exceptionCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;
    // ((+ 1 2))
    const std::vector<Token> sample = {
            Token(Token::OpenBracket, "(", 1, 1),
            Token(Token::OpenBracket, "(", 1, 2),
            Token(Token::Symbol, "+", 1, 3),
            Token(Token::Integer, "1", 1, 5),
            Token(Token::Integer, "2", 1, 7),
            Token(Token::ClosedBracket, ")", 1, 8),
            Token(Token::ClosedBracket, ")", 1, 9),
    };

    try {
        Parser::parse(sample);
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(errorMessage == "An atom was expected after the opening parenthesis but not found", true);
    EXPECT_EQ(line == sample[0].line, true);
    EXPECT_EQ(column == sample[0].column, true);
}

TEST(parse_test, ShouldThrowExceptionsOnEmptyParenthesis) {
    bool exceptionCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;
    // ((+ 1 2))
    const std::vector<Token> sample = {
            Token(Token::OpenBracket, "(", 1, 1),
            Token(Token::ClosedBracket, ")", 1, 2),
    };

    try {
        Parser::parse(sample);
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(errorMessage == "An atom was expected after the opening parenthesis but not found", true);
    EXPECT_EQ(line == sample[0].line, true);
    EXPECT_EQ(column == sample[0].column, true);
}
