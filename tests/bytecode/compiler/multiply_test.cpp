#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/Store.h"
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

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Multiply(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileSimpleMultiplicationWithOptimization) {
    // (* 12 74)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
            });

    auto expected_result = Program({
            new Segment({new LoadLiteral(888)}),
    });

    Compiler compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, IgnoreOptimizationWhenNotPossible) {
    // (define x 12)
    const auto first_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(12)),
            });
    // (* 12 74)
    const auto second_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new Store(new GlobalRegister(0)),
                    new Load(new GlobalRegister(0)),
                    new LoadLiteral(74),
                    new Multiply(),
            }),
    });

    Compiler compiler = Compiler(true);
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
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
    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Multiply(),
                    new LoadLiteral(17),
                    new Multiply(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileLongMultiplicationWithOptimization) {
    // (* 12 74 17)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(new Token(12)),
                    new SyntaxTreeNode(new Token(74)),
                    new SyntaxTreeNode(new Token(17)),
            });
    auto expected_result = Program({
            new Segment({new LoadLiteral(15096)}),
    });

    Compiler compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileNestedMultiplication) {
    // (* (* 23 74) 43)
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
    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(23),
                    new LoadLiteral(74),
                    new Multiply(),
                    new LoadLiteral(43),
                    new Multiply(),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileNestedMultiplicationWithOptimization) {
    // (* (* 23 74) 43)
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
    auto expected_result = Program({
            new Segment({new LoadLiteral(73186)}),
    });

    Compiler compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
