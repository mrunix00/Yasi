#include "../src/lexer/Lexer.h"
#include <gtest/gtest.h>
#include <vector>

TEST(lex_test, ShouldTokenizeSingleToken) {
    std::string sample = "32";
    std::vector<Token *> expected = {new Token(Token::Integer, "32")};
    auto actual = Lexer::tokenize(sample);
    EXPECT_EQ(*expected[0] == *actual[0], true);
}

TEST(lex_test, ShouldTokenizeSingleChars) {
    std::string sample = "(+ 1 2)";
    std::vector<Token *> tokens = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "+"),
            new Token(Token::Integer, "1"),
            new Token(Token::Integer, "2"),
            new Token(Token::ClosedBracket, ")"),
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens.size() == result.size(), true);
    for (int i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(*tokens[i] == *result[i], true);
    }
}

TEST(lex_test, ShouldTokenizeMultipleChars) {
    std::string sample = "(multiply 1 2)";
    std::vector<Token *> tokens = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "multiply"),
            new Token(Token::Integer, "1"),
            new Token(Token::Integer, "2"),
            new Token(Token::ClosedBracket, ")"),
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens.size() == result.size(), true);
    for (int i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(*tokens[i] == *result[i], true);
    }
}

TEST(lex_test, ShouldTokenizeLargeNumbers) {
    std::string sample = "(+ 13 54)";
    std::vector<Token *> tokens = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "+"),
            new Token(Token::Integer, "13"),
            new Token(Token::Integer, "54"),
            new Token(Token::ClosedBracket, ")"),
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens.size() == result.size(), true);
    for (int i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(*tokens[i] == *result[i], true);
    }
}

TEST(lex_test, ShouldTokenizeNegativeNumbers) {
    std::string sample = "(+ 1 -1)";
    std::vector<Token *> tokens = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "+"),
            new Token(Token::Integer, "1"),
            new Token(Token::Integer, "-1"),
            new Token(Token::ClosedBracket, ")"),
    };

    auto result = Lexer::tokenize(sample);

    EXPECT_EQ(tokens.size() == result.size(), true);
    for (int i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(*tokens[i] == *result[i], true);
    }
}

TEST(lex_test, StringsToken) {
    std::string sample = "(print \"Hello World\")";
    std::vector<Token *> expected = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "print"),
            new Token(Token::String, "\"Hello World\""),
            new Token(Token::ClosedBracket, ")"),
    };

    auto actual = Lexer::tokenize(sample);

    EXPECT_EQ(expected.size() == actual.size(), true);
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(*expected[i] == *actual[i], true);
    }
}

TEST(lex_test, DecimalTokens) {
    const std::string sample = "(+ 1.2 3)";
    const std::vector<Token *> expected = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "+"),
            new Token(Token::Decimal, "1.2"),
            new Token(Token::Integer, "3"),
            new Token(Token::ClosedBracket, ")"),
    };

    auto actual = Lexer::tokenize(sample);

    EXPECT_EQ(expected.size() == actual.size(), true);
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(*expected[i] == *actual[i], true);
    }
}

TEST(lex_test, ShouldLocateTokens) {
    std::string sample = "(+ 12 54)";
    auto tokens = Lexer::tokenize(sample);

    EXPECT_EQ(tokens[0]->line == 1, true);
    EXPECT_EQ(tokens[0]->column, true);

    EXPECT_EQ(tokens[1]->line == 1, true);
    EXPECT_EQ(tokens[1]->column == 2, true);

    EXPECT_EQ(tokens[2]->line == 1, true);
    EXPECT_EQ(tokens[2]->column == 4, true);

    EXPECT_EQ(tokens[3]->line == 1, true);
    EXPECT_EQ(tokens[3]->column == 7, true);

    EXPECT_EQ(tokens[4]->line == 1, true);
    EXPECT_EQ(tokens[4]->column == 9, true);
}

TEST(lex_test, ShouldLocateTokensOnMultiLineExpressions) {
    std::string sample = "(+\n1 2\n)";
    auto tokens = Lexer::tokenize(sample);

    EXPECT_EQ(tokens[0]->line == 1, true);
    EXPECT_EQ(tokens[0]->column == 1, true);

    EXPECT_EQ(tokens[1]->line == 1, true);
    EXPECT_EQ(tokens[1]->column == 2, true);

    EXPECT_EQ(tokens[2]->line == 2, true);
    EXPECT_EQ(tokens[2]->column == 1, true);

    EXPECT_EQ(tokens[3]->line == 2, true);
    EXPECT_EQ(tokens[3]->column == 3, true);

    EXPECT_EQ(tokens[4]->line == 3, true);
    EXPECT_EQ(tokens[4]->column == 1, true);
}
