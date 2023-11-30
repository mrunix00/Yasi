#include <gtest/gtest.h>
#include "lexer/Lexer.h"

TEST(token_test, TokensEqualityCheck) {
    auto token1 = Token(Token::OpenBracket, "(");
    auto token2 = Token(Token::OpenBracket, "(");
    auto token3 = Token(Token::Symbol, "+");
    auto token4 = Token(Token::Symbol, "-");

    EXPECT_EQ(token1 == token2, true);
    EXPECT_EQ(token2 == token3, false);
    EXPECT_EQ(token3 == token4, false);
}