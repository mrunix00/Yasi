#include <gtest/gtest.h>
#include "../src/Parser/AbstractSyntaxTree.h"
#include "../src/Parser/parse.h"

TEST(parse_test, ParseSimpleOperation) {
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")"),
    };
    auto expected = AbstractSyntaxTree(
            Token(Token::Symbol, "+"),
            {
                    Argument(Token(Token::Integer, "1")),
                    Argument(Token(Token::Integer, "2"))
            }
    );

    auto actual = parse(sample);

    EXPECT_EQ(actual == expected, true);
}

TEST(parse_test, ParseSimpleOperationWithStringArgument) {
    auto sample = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "print"),
            Token(Token::String, "\"Hello World\""),
            Token(Token::ClosedBracket, ")"),
    };
    auto expected = AbstractSyntaxTree(
            Token(Token::Symbol, "print"),
            {
                    Argument(Token(Token::String, "\"Hello World\"")
                    ),
            }
    );

    auto actual = parse(sample);

    EXPECT_EQ(actual == expected, true);
}