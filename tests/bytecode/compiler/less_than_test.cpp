#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_less, CompileSimpleLessThanCheck) {
    // (< 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "<"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(74),
            new LessThan(),
    };
    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_less, CompileLongLessThanCheck) {
    // (< 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "<"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(12),
            new LessThan(),
            new LoadLiteral(74),
            new LessThan(),
    };
    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}
