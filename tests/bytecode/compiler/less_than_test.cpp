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
            Token(Token::Symbol, "<"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new LessThan(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_less, CompileLongLessThanCheck) {
    // (< 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "<"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(12),
                    new LessThan(),
                    new LoadLiteral(74),
                    new LessThan(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
