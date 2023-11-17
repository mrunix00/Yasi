#include <gtest/gtest.h>
#include "../src/Tokens/Token.h"
#include "../src/Lexer/Lexer.h"

TEST(lex_test, ShouldTokenizeSingleChars) {
    std::string sample = "(+ 1 2)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")")
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeMultipleChars) {
    std::string sample = "(multiply 1 2)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "multiply"),
            Token(Token::Integer, "1"),
            Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")")
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeLargeNumbers) {
    std::string sample = "(+ 13 54)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("),
            Token(Token::Symbol, "+"),
            Token(Token::Integer, "13"),
            Token(Token::Integer, "54"),
            Token(Token::ClosedBracket, ")")
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}