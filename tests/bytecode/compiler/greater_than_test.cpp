#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_greater, CompileSimpleGreaterThanCheck) {
    // (> 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, ">"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(74),
            new GreaterThan(),
    };
    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_greater, CompileLongGreaterThanCheck) {
    // (> 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, ">"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(12),
            new LoadLiteral(12),
            new GreaterThan(),
            new LoadLiteral(74),
            new GreaterThan(),
    };
    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}
