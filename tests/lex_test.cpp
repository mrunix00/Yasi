#include <gtest/gtest.h>
#include "../src/Tokens/Tokens.h"
#include "../src/Lexer/Lexer.h"

TEST(lex_test, ShouldTokenizeSingleChars) {
    std::string sample = "(+ 1 2)";
    std::vector<Token> tokens = {
            OpenBracket(),
            Symbol("+"),
            Integer(1),
            Integer(2),
            ClosedBracket()
    };

    auto result = Lexer::tokenizer(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeMultipleChars) {
    std::string sample = "(multiply 1 2)";
    std::vector<Token> tokens = {
            OpenBracket(),
            Symbol("multiply"),
            Integer(1),
            Integer(2),
            ClosedBracket()
    };

    auto result = Lexer::tokenizer(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeLargeNumbers) {
    std::string sample = "(+ 13 54)";
    std::vector<Token> tokens = {
            OpenBracket(),
            Symbol("+"),
            Integer(13),
            Integer(54),
            ClosedBracket()
    };

    auto result = Lexer::tokenizer(sample);

    EXPECT_EQ(tokens == result, true);
}