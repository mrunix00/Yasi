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

    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
            Token(Token::ClosedBracket, ")")};

    try {
        Parser::parse(sample);
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        actualErrorMessage = error.message;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(expectedErrorMessage == actualErrorMessage, true);
}
