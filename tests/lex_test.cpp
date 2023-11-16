#include <gtest/gtest.h>
#include "../src/Tokens/Tokens.h"
#include "../src/Lexer/Lexer.h"

TEST(lex_test, ShouldSingleCharsParseIntoTokens) {
    std::string sample = "(+ 1 2)";
    std::vector<Token> tokens = {
            OpenBracket(),
            Symbol("+"),
            Integer(1),
            Integer(2),
            ClosedBracket()
    };

    auto result = Lexer::parse(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldMultipleCharsParseIntoTokens) {
    std::string sample = "(multiply 1 2)";
    std::vector<Token> tokens = {
            OpenBracket(),
            Symbol("multiply"),
            Integer(1),
            Integer(2),
            ClosedBracket()
    };

    auto result = Lexer::parse(sample);

    EXPECT_EQ(tokens == result, true);
}