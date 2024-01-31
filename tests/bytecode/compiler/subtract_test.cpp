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

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(100),
                    new LoadLiteral(32),
                    new Subtract(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_subtract, CompileLongSubtraction) {
    // (- 120 60 39)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "-"),
            {
                    new SyntaxTreeNode(new Token(120)),
                    new SyntaxTreeNode(new Token(60)),
                    new SyntaxTreeNode(new Token(39)),
            });
    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(120),
                    new LoadLiteral(60),
                    new Subtract(),
                    new LoadLiteral(39),
                    new Subtract(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_subtract, CompileNestedSubtraction) {
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
    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(153),
                    new LoadLiteral(74),
                    new Subtract(),
                    new LoadLiteral(43),
                    new Subtract(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
