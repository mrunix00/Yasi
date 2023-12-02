#include "builtin_functions/print/print.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(print_test, ShouldPrintStringArgument) {
    const std::vector<SyntaxTreeNode> args = {
            SyntaxTreeNode(Token(Token::String, "\"Hello World\"")),
    };

    const auto actual = Print().evaluate(args);

    EXPECT_EQ(actual.token.token == "Hello World", true);
}

TEST(print_test, ShouldPrintMultipleStringArguments) {
    const std::vector<SyntaxTreeNode> args = {
            SyntaxTreeNode(Token(Token::String, "\"Hello\"")),
            SyntaxTreeNode(Token(Token::String, "\" World\"")),
    };

    const auto expected = SyntaxTreeNode(Token(Token::String, "Hello World"));
    const auto actual = Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}

TEST(print_test, ShouldPrintIntegers) {
    const std::vector<SyntaxTreeNode> args = {
            SyntaxTreeNode(Token(Token::Integer, "1")),
            SyntaxTreeNode(Token(Token::Integer, "2")),
    };

    const auto expected = SyntaxTreeNode(Token(Token::String, "12"));
    const auto actual = Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}

TEST(print_test, ShouldEvaluateOperandsBeforePrinting) {
    const std::vector<SyntaxTreeNode> args = {
            SyntaxTreeNode(Token(Token::String, "\"The result is: \"")),
            SyntaxTreeNode(
                    Token(Token::Symbol, "+"),
                    {
                            SyntaxTreeNode(Token(Token::Integer, "1")),
                            SyntaxTreeNode(Token(Token::Integer, "2")),
                    }),
    };

    const auto expected = SyntaxTreeNode(Token(Token::String, "The result is: 3"));
    const auto actual = Print().evaluate(args);

    EXPECT_EQ(actual == expected, true);
}
