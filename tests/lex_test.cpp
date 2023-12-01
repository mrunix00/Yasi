#include "../src/lexer/Lexer.h"
#include <gtest/gtest.h>

TEST(lex_test, ShouldTokenizeSingleChars) {
    std::string sample = "(+ 1 2)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("), Token(Token::Symbol, "+"),
            Token(Token::Integer, "1"), Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")")};

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeMultipleChars) {
    std::string sample = "(multiply 1 2)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("), Token(Token::Symbol, "multiply"),
            Token(Token::Integer, "1"), Token(Token::Integer, "2"),
            Token(Token::ClosedBracket, ")")};

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, ShouldTokenizeLargeNumbers) {
    std::string sample = "(+ 13 54)";
    std::vector<Token> tokens = {
            Token(Token::OpenBracket, "("), Token(Token::Symbol, "+"),
            Token(Token::Integer, "13"), Token(Token::Integer, "54"),
            Token(Token::ClosedBracket, ")")};

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens == result, true);
}

TEST(lex_test, StringsToken) {
    std::string sample = "(print \"Hello World\")";
    std::vector<Token> expected = {Token(Token::OpenBracket, "("),
                                   Token(Token::Symbol, "print"),
                                   Token(Token::String, "\"Hello World\""),
                                   Token(Token::ClosedBracket, ")")};

    auto actual = Lexer::tokenize(sample);

    EXPECT_EQ(expected == actual, true);
}

TEST(lex_test, ShouldLocateTokens) {
    std::string sample = "(+ 12 54)";
    auto tokens = Lexer::tokenize(sample);

    EXPECT_EQ(tokens[0].line == 1, true);
    EXPECT_EQ(tokens[0].column, true);

    EXPECT_EQ(tokens[1].line == 1, true);
    EXPECT_EQ(tokens[1].column == 2, true);

    EXPECT_EQ(tokens[2].line == 1, true);
    EXPECT_EQ(tokens[2].column == 4, true);

    EXPECT_EQ(tokens[3].line == 1, true);
    EXPECT_EQ(tokens[3].column == 7, true);

    EXPECT_EQ(tokens[4].line == 1, true);
    EXPECT_EQ(tokens[4].column == 9, true);
}

TEST(lex_test, ShouldLocateTokensOnMultiLineExpressions) {
    std::string sample = "(+\n1 2\n)";
    auto tokens = Lexer::tokenize(sample);

    EXPECT_EQ(tokens[0].line == 1, true);
    EXPECT_EQ(tokens[0].column == 1, true);

    EXPECT_EQ(tokens[1].line == 1, true);
    EXPECT_EQ(tokens[1].column == 2, true);

    EXPECT_EQ(tokens[2].line == 2, true);
    EXPECT_EQ(tokens[2].column == 1, true);

    EXPECT_EQ(tokens[3].line == 2, true);
    EXPECT_EQ(tokens[3].column == 3, true);

    EXPECT_EQ(tokens[4].line == 3, true);
    EXPECT_EQ(tokens[4].column == 1, true);
}
