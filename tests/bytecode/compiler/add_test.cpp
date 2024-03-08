#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/objects/GlobalRegister.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_add, CompileSimpleAddition) {
    // (+ 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    const auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(12),
                            new LoadLiteral(74),
                            new Add(),
                    }),
    });
    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileSimpleAdditionWithOptimization) {
    // (+ 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    const auto expected_result = Program({
            new Segment({new LoadLiteral(86)}),
    });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, DontOptimizeIfNotPossible) {
    // (define x 12)
    const auto first_expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(12)),
            });
    // (+ x 74)
    const auto second_expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(74)),
            });

    auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(12),
                            new Store(new GlobalRegister(0)),
                            new LoadGlobal(0),
                            new LoadLiteral(74),
                            new Add(),
                    }),
    });

    auto compiler = Compiler(true);
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileLongAddition) {
    // (+ 12 74 17)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
                    new SyntaxTreeNode(Token(17)),
            });
    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(12),
                            new LoadLiteral(74),
                            new Add(),
                            new LoadLiteral(17),
                            new Add(),
                    }),
            });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileLongAdditionWithOptimization) {
    // (+ 12 74 17)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
                    new SyntaxTreeNode(Token(17)),
            });
    const auto expected_result = Program(
            {
                    new Segment({new LoadLiteral(103)}),
            });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileNestedAddition) {
    // (+ (+ 23 74) 43)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(Token(23)),
                                    new SyntaxTreeNode(Token(74)),
                            }),
                    new SyntaxTreeNode(Token(43)),
            });
    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(23),
                            new LoadLiteral(74),
                            new Add(),
                            new LoadLiteral(43),
                            new Add(),
                    }),
            });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileNestedAdditionWithOptimization) {
    // (+ (+ 23 74) 43)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(Token(23)),
                                    new SyntaxTreeNode(Token(74)),
                            }),
                    new SyntaxTreeNode(Token(43)),
            });
    const auto expected_result = Program(
            {
                    new Segment({new LoadLiteral(140)}),
            });

    auto compiler = Compiler(true);
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_add, CompileAddtionWithDecimalNumbers) {
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(static_cast<double>(3.14))),
                    new SyntaxTreeNode(Token(43)),
            });
    const auto expected_result = Program({new Segment({
            new LoadLiteral(3.14),
            new LoadLiteral(43),
            new Add(),
    })});

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}