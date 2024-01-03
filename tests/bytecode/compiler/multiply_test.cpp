#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_multiply, CompileSimpleMultiplication) {
    // (* 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(74),
            new Multiply(),
    };
    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_multiply, CompileLongMultiplication) {
    // (* 12 74 17)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
                    new SyntaxTreeNode(new Token(17)),
            });
    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(74),
            new Multiply(),
            new LoadLiteral(17),
            new Multiply(),
    };

    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_multiply, CompileNestedMultiplication) {
    // (+ (+ 23 74) 43)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(23)),
                                    new SyntaxTreeNode(new Token(74)),
                            }),
                    new SyntaxTreeNode(new Token(43)),
            });
    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(23),
            new LoadLiteral(74),
            new Multiply(),
            new LoadLiteral(43),
            new Multiply(),
    };

    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}
