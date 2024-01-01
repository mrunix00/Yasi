#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Subtract.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_subtract, CompileSimpleSubtraction) {
    // (- 100 32)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "-"),
            {
                    new SyntaxTreeNode(new Token(100)),
                    new SyntaxTreeNode(new Token(32)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(100),
            new LoadLiteral(32),
            new Subtract(),
    };

    std::vector<Instruction> actual_result;
    Compiler::compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_add, CompileLongSubtraction) {
    // (- 120 60 39)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "-"),
            {
                    new SyntaxTreeNode(new Token(120)),
                    new SyntaxTreeNode(new Token(60)),
                    new SyntaxTreeNode(new Token(39)),
            });
    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(120),
            new LoadLiteral(60),
            new Subtract(),
            new LoadLiteral(39),
            new Subtract(),
    };

    std::vector<Instruction> actual_result;
    Compiler::compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_add, CompileNestedSubtraction) {
    // (- (- 153 74) 43)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "-"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "-"),
                            {
                                    new SyntaxTreeNode(new Token(153)),
                                    new SyntaxTreeNode(new Token(74)),
                            }),
                    new SyntaxTreeNode(new Token(43)),
            });
    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(153),
            new LoadLiteral(74),
            new Subtract(),
            new LoadLiteral(43),
            new Subtract(),
    };

    std::vector<Instruction> actual_result;
    Compiler::compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(actual_result[i], *expected_result[i]);
    }
}
