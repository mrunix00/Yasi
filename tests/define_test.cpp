#include "builtin_functions/define/define.h"
#include "eval/eval.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

TEST(define_test, ShouldDefineAVariable) {
    Define().evaluate({SyntaxTreeNode(Token(Token::Symbol, "x")),
                       SyntaxTreeNode(Token(Token::Integer, "15"))});

    auto expression = SyntaxTreeNode(Token(Token::Symbol, "+"),
                                     {
                                             SyntaxTreeNode(Token(Token::Integer, "5")),
                                             SyntaxTreeNode(Token(Token::Symbol, "x")),
                                     });
    auto expected_result = SyntaxTreeNode(Token(Token::Integer, "20"));
    auto actual_result = Evaluate::evaluate(expression);

    EXPECT_EQ(actual_result == expected_result, true);
}
