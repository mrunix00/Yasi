#include <gtest/gtest.h>
#include "../src/Parser/parse.h"

TEST(parse_test, ParseSimpleOperation) {
    // ( + 1 2 )
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
    };
    auto expected = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "2"))
            }
    );

    auto actual = parse(sample);

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
            }
    );

    auto actual = parse(sample);

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
            {
                    SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    SyntaxTreeNode(Token(Token::Integer, "1")),
                                    SyntaxTreeNode(Token(Token::Integer, "3"))
                            }
                    ),
                    SyntaxTreeNode(Token(Token::Integer, "2"))
            }
    );

    auto actual = parse(sample);

    EXPECT_EQ(actual == expected, true);
}