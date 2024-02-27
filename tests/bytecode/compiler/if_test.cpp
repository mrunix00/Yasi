#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/Jump.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_if, SimpleConditionalStatement) {
    // (if (> 20 10) 20)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "if"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(Token(20)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
                    new SyntaxTreeNode(Token(20)),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(5),
                            new LoadLiteral(20),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_if, SimpleConditionWithElseClause) {
    // (if (> 20 10) 20 10)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "if"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(Token(20)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
                    new SyntaxTreeNode(Token(20)),
                    new SyntaxTreeNode(Token(10)),
            });

    const auto expected_result = Program(
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

TEST(compiler_if, LongCondition) {
    // (if (> 20 10) (+ 10 10))
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "if"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(Token(20)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(Token(10)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(7),
                            new LoadLiteral(10),
                            new LoadLiteral(10),
                            new Add(),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_if, LongConditionWithElseClause) {
    // (if (> 20 10) (+ 10 10) (+ 5 5))
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "if"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, ">"),
                            {
                                    new SyntaxTreeNode(Token(20)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(Token(10)),
                                    new SyntaxTreeNode(Token(10)),
                            }),
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(Token(5)),
                                    new SyntaxTreeNode(Token(5)),
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
