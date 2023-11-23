#include <gtest/gtest.h>
#include "../src/parser/SyntaxTreeNode.h"
#include "../src/eval/eval.h"

TEST(eval_test, ShouldEvaluateSimpleSumExpression) {
    auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "1")),
                    SyntaxTreeNode(Token(Token::Integer, "2"))
            }
    );

    auto expectedResult = SyntaxTreeNode(
            Token(Token::Integer, "3")
    );

    auto actualResult = evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleMultiplication) {
    auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "3")),
                    SyntaxTreeNode(Token(Token::Integer, "2"))
            }
    );

    auto expectedResult = SyntaxTreeNode(
            Token(Token::Integer, "6")
    );

    auto actualResult = evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}

TEST(eval_test, ShouldEvaluateSimpleSubtraction) {
    auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "-"),
            {
                    SyntaxTreeNode(Token(Token::Integer, "70")),
                    SyntaxTreeNode(Token(Token::Integer, "2"))
            }
    );

    auto expectedResult = SyntaxTreeNode(
            Token(Token::Integer, "68")
    );

    auto actualResult = evaluate(expression);

    EXPECT_EQ(expectedResult == actualResult, true);
}