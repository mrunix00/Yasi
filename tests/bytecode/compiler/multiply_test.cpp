#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/StoreGlobal.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_multiply, CompileSimpleMultiplication) {
    // (* 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    const auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Multiply(),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileSimpleMultiplicationWithOptimization) {
    // (* 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    const auto expected_result = Program({
            new Segment({new LoadLiteral(888)}),
    });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, IgnoreOptimizationWhenNotPossible) {
    // (define x 12)
    const auto first_expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(12)),
            });
    // (* 12 74)
    const auto second_expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(74)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new StoreGlobal(0),
                    new LoadGlobal(0),
                    new LoadLiteral(74),
                    new Multiply(),
            }),
    });

    auto compiler = Compiler(true);
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileLongMultiplication) {
    // (* 12 74 17)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
                    new SyntaxTreeNode(Token(17)),
            });
    const auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Multiply(),
                    new LoadLiteral(17),
                    new Multiply(),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileLongMultiplicationWithOptimization) {
    // (* 12 74 17)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
                    new SyntaxTreeNode(Token(17)),
            });
    const auto expected_result = Program({
            new Segment({new LoadLiteral(15096)}),
    });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileNestedMultiplication) {
    // (* (* 23 74) 43)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(Token(23)),
                                    new SyntaxTreeNode(Token(74)),
                            }),
                    new SyntaxTreeNode(Token(43)),
            });
    const auto expected_result = Program({
            new Segment({
                    new LoadLiteral(23),
                    new LoadLiteral(74),
                    new Multiply(),
                    new LoadLiteral(43),
                    new Multiply(),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_multiply, CompileNestedMultiplicationWithOptimization) {
    // (* (* 23 74) 43)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "*"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(Token(23)),
                                    new SyntaxTreeNode(Token(74)),
                            }),
                    new SyntaxTreeNode(Token(43)),
            });
    const auto expected_result = Program({
            new Segment({new LoadLiteral(73186)}),
    });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
