#include "../src/parser/Parser.h"
#include "exceptions/SyntaxError.h"
#include <gtest/gtest.h>

TEST(parse_test, ReturnNullWhenGivenNoTokens) {
    const auto actual = parse({});
    EXPECT_EQ(actual == nullptr, true);
}

TEST(parse_test, ParseSingleToken) {
    auto sample = "2";

    auto expected = TokenNode(Token(Token::Number, "2"));
    auto actual = parse(tokenize(sample));

    EXPECT_EQ(expected == *actual, true);
}

TEST(parse_test, ParseSimpleOperation) {
    const auto sample = "(+ 1 2)";

    const auto expected = Expression(
            Token(Token::Symbol, "+"),
            {
                    new TokenNode(Token(Token::Number, "1")),
                    new TokenNode(Token(Token::Number, "2")),
            });
    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ParseSimpleOperationWithStringArgument) {
    const auto sample = "(print \"Hello World\")";
    const auto expected = Expression(
            Token(Token::Symbol, "print"),
            {
                    new TokenNode(Token(Token::String, "\"Hello World\"")),
            });

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ParseNestedOperation) {
    // ( + ( + 1 3 ) 2 )
    const auto sample = "( + ( + 1 3 ) 2 )";

    const auto expected = Expression(
            Token(Token::Symbol, "+"),
            {
                    new Expression(
                            Token(Token::Symbol, "+"),
                            {
                                    new TokenNode(Token(Token::Number, "1")),
                                    new TokenNode(Token(Token::Number, "3")),
                            }),
                    new TokenNode(Token(Token::Number, "2")),
            });

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ParseDeeplyNestedOperation) {
    const auto sample = "( + ( * 2 3 ) ( + ( * 1 2 ) 4 ) 7 )";

    const auto expected = Expression(
            Token(Token::Symbol, "+"),
            {
                    new Expression(
                            Token(Token::Symbol, "*"),
                            {
                                    new TokenNode(Token(Token::Number, "2")),
                                    new TokenNode(Token(Token::Number, "3")),
                            }),
                    new Expression(
                            Token(Token::Symbol, "+"),
                            {
                                    new Expression(
                                            Token(Token::Symbol, "*"),
                                            {
                                                    new TokenNode(Token(Token::Number, "1")),
                                                    new TokenNode(Token(Token::Number, "2")),
                                            }),
                                    new TokenNode(Token(Token::Number, "4")),
                            }),
                    new TokenNode(Token(Token::Number, "7")),
            });

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseASimpleCondStatement) {
    const auto sample = "(cond ((= x 1) 2))";

    const auto expected = CondExpression(
            {
                    {
                            new Expression(
                                    Token(Token::Symbol, "="),
                                    {
                                            new TokenNode(Token(Token::Symbol, "x")),
                                            new TokenNode(Token(Token::Number, "1")),
                                    }),
                            new TokenNode(Token(Token::Number, "2")),
                    },
            },
            nullptr);

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseACondStatementWithDefaultCase) {
    const auto sample = "(cond ((= 1 1) 1) (else 2))";

    const auto expected = CondExpression(
            {
                    {
                            new Expression(
                                    Token(Token::Symbol, "="),
                                    {
                                            new TokenNode(Token(Token::Number, "1")),
                                            new TokenNode(Token(Token::Number, "1")),
                                    }),
                            new TokenNode(Token(Token::Number, "1")),
                    },
            },
            new TokenNode(Token(Token::Number, "2")));

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseACondStatement) {
    const auto sample = "(cond ((= 1 1) 1) ((= 2 2) 2) (else 3))";

    const auto expected = CondExpression(
            {
                    {
                            new Expression(
                                    Token(Token::Symbol, "="),
                                    {
                                            new TokenNode(Token(Token::Number, "1")),
                                            new TokenNode(Token(Token::Number, "1")),
                                    }),
                            new TokenNode(Token(Token::Number, "1")),
                    },
                    {
                            new Expression(
                                    Token(Token::Symbol, "="),
                                    {
                                            new TokenNode(Token(Token::Number, "2")),
                                            new TokenNode(Token(Token::Number, "2")),
                                    }),
                            new TokenNode(Token(Token::Number, "2")),
                    },
            },
            new TokenNode(Token(Token::Number, "3")));

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseALambdaExpressionWithOneArgument) {
    const auto sample = "(lambda (x) (+ x 1))";

    const auto expected = LambdaExpression(
            {
                    new TokenNode(Token(Token::Symbol, "x")),
            },
            new Expression(
                    Token(Token::Symbol, "+"),
                    {
                            new TokenNode(Token(Token::Symbol, "x")),
                            new TokenNode(Token(Token::Number, "1")),
                    }));

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseALambdaExpressionWithLambdaSymbol) {
    const auto sample = "(λ (x) (+ x 1))";

    const auto expected = LambdaExpression(
            {
                    new TokenNode(Token(Token::Symbol, "x")),
            },
            new Expression(
                    Token(Token::Symbol, "+"),
                    {
                            new TokenNode(Token(Token::Symbol, "x")),
                            new TokenNode(Token(Token::Number, "1")),
                    }));

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldParseALambdaExpressionWithMultipleArguments) {
    const auto sample = "(lambda (x y) (+ x y))";

    const auto expected = LambdaExpression(
            {
                    new TokenNode(Token(Token::Symbol, "x")),
                    new TokenNode(Token(Token::Symbol, "y")),
            },
            new Expression(
                    Token(Token::Symbol, "+"),
                    {
                            new TokenNode(Token(Token::Symbol, "x")),
                            new TokenNode(Token(Token::Symbol, "y")),
                    }));

    const auto actual = parse(tokenize(sample));

    EXPECT_EQ(*actual == expected, true);
}

TEST(parse_test, ShouldThrowExceptionsOnExtraParenthesis) {
    auto exceptionCaught = false;
    const auto expectedErrorMessage = "Unexpected parenthesis -> ')'";
    std::string actualErrorMessage;
    int extraParenthesisLine;
    int extraParenthesisColumn;

    const auto sample = "(+ 1 2))";

    try {
        parse(tokenize(sample));
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        actualErrorMessage = error.message;
        extraParenthesisLine = error.line;
        extraParenthesisColumn = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(expectedErrorMessage == actualErrorMessage, true);
    EXPECT_EQ(extraParenthesisLine, 1);
    EXPECT_EQ(extraParenthesisColumn, 8);
}

TEST(parse_test, ShouldThrowExceptionsOnMissingOperator) {
    bool exceptionCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;
    const auto sample = "((+ 1 2))";

    try {
        parse(tokenize(sample));
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(errorMessage == "An atom was expected after the opening parenthesis but not found", true);
    EXPECT_EQ(line, 1);
    EXPECT_EQ(column, 1);
}

TEST(parse_test, ShouldThrowExceptionsOnEmptyParenthesis) {
    bool exceptionCaught = false;
    std::string errorMessage;
    int line = 0;
    int column = 0;
    const auto sample = "((+ 1 2))";

    try {
        parse(tokenize(sample));
    } catch (SyntaxError &error) {
        exceptionCaught = true;
        errorMessage = error.message;
        line = error.line;
        column = error.column;
    }

    EXPECT_EQ(exceptionCaught, true);
    EXPECT_EQ(errorMessage == "An atom was expected after the opening parenthesis but not found", true);
    EXPECT_EQ(line, 1);
    EXPECT_EQ(column, 1);
}