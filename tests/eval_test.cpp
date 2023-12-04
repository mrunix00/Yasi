#include "../src/eval/eval.h"
#include "../src/parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(eval_test, ShouldEvaluateSimpleSumExpression) {
    auto expression =
            SyntaxTreeNode(Token(Token::Symbol, "+"),
                           {SyntaxTreeNode(Token(Token::Integer, "1")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))});

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "3"));

    auto actualResult = Evaluate::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleMultiplication) {
    auto expression =
            SyntaxTreeNode(Token(Token::Symbol, "*"),
                           {SyntaxTreeNode(Token(Token::Integer, "3")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))});

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "6"));

    auto actualResult = Evaluate::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleSubtraction) {
    auto expression =
            SyntaxTreeNode(Token(Token::Symbol, "-"),
                           {SyntaxTreeNode(Token(Token::Integer, "70")),
                            SyntaxTreeNode(Token(Token::Integer, "2"))});

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "68"));

    auto actualResult = Evaluate::evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateNestedExpression) {
    auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {SyntaxTreeNode(Token(Token::Symbol, "-"),
                            {SyntaxTreeNode(Token(Token::Integer, "32")),
                             SyntaxTreeNode(Token(Token::Integer, "2"))}),
             SyntaxTreeNode(Token(Token::Integer, "7"))});

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "37"));
    auto actualResult = Evaluate::evaluate(expression);
    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldCallFunctionWithNoArguments) {
    auto expression = SyntaxTreeNode(
        Token(Token::Symbol, "+")
    );

    auto expectedResult = SyntaxTreeNode(Token(Token::Integer, "0"));
    auto actualResult = Evaluate::evaluate(expression);
    EXPECT_EQ(expectedResult == actualResult, true);
}
