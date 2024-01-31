#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_equals, CompileSimpleEqualityCheck) {
    // (= 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Equals(),
            }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_equals, CompileLongEqualityCheck) {
    // (= 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "="),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(12),
                    new Equals(),
                    new LoadLiteral(74),
                    new Equals(),
            }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
