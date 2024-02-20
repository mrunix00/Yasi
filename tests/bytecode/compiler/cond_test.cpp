#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/Jump.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "lexer/Token.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_cond, CompileSimpleCondition) {
    // (cond (> 20 10) 20)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "cond"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(new Token(20)),
            });

    auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(6),
                            new LoadLiteral(20),
                            new Jump(6),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_cond, SimpleConditionWithElseClause) {
    // (cond (> 20 10) 20 10)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "cond"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(new Token(20)),
                    new SyntaxTreeNode(new Token(10)),
            });

    auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(6),
                            new LoadLiteral(20),
                            new Jump(7),
                            new LoadLiteral(10),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_cond, LongCondition) {
    // (cond (> 20 10) (+ 10 10))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "cond"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(10)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(8),
                            new LoadLiteral(10),
                            new LoadLiteral(10),
                            new Add(),
                            new Jump(8),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_cond, LongConditionWithElseClause) {
    // (if (cond 20 10) (+ 10 10) (+ 5 5))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "cond"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(10)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(5)),
                                    new SyntaxTreeNode(new Token(5)),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(8),
                            new LoadLiteral(10),
                            new LoadLiteral(10),
                            new Add(),
                            new Jump(11),
                            new LoadLiteral(5),
                            new LoadLiteral(5),
                            new Add(),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_cond, TestMultipleCases) {
    // (cond (> 20 10) (+ 10 10) (< 20 10) (+ 5 5) (+ 2 2))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "cond"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(10)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "<"),
                            {
                                    new SyntaxTreeNode(new Token(20)),
                                    new SyntaxTreeNode(new Token(10)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(5)),
                                    new SyntaxTreeNode(new Token(5)),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(2)),
                                    new SyntaxTreeNode(new Token(2)),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(8),
                            new LoadLiteral(10),
                            new LoadLiteral(10),
                            new Add(),
                            new Jump(19),
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new LessThan(),
                            new CondJumpIfNot(16),
                            new LoadLiteral(5),
                            new LoadLiteral(5),
                            new Add(),
                            new Jump(19),
                            new LoadLiteral(2),
                            new LoadLiteral(2),
                            new Add(),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}