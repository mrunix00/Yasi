#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/Jump.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/Subtract.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_functions, SimpleFunctionDefinition) {
    // (define (square x) (* x x))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "square"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            }),
            });

    auto expected_result = Program(
            {
                    new Segment({}),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(0)),
                            new Multiply(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_functions, FunctionDefinitionWithMultipleArgs) {
    // (define (add x y) (+ x y))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "add"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({}),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(1)),
                            new Add(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_functions, SimpleFunctionCall) {
    // (define (square x) (* x x))
    const auto function_definition = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "square"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            }),
            });

    // (square 15)
    const auto function_call = SyntaxTreeNode(
            new Token(Token::Symbol, "square"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "15")),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(15),
                            new Call(1, 1),
                    }),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(0)),
                            new Multiply(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(function_definition);
    compiler.compile(function_call);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_functions, FunctionWithMultipleArgsCall) {
    // (define (add x y) (+ x y))
    const auto function_definition = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "add"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "+"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
            });

    // (add 20 30)
    const auto function_call = SyntaxTreeNode(
            new Token(Token::Symbol, "add"),
            {
                    new SyntaxTreeNode(new Token(20)),
                    new SyntaxTreeNode(new Token(30)),
            });

    const auto expected_result = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(30),
                            new Call(1, 2),
                    }),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(1)),
                            new Add(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(function_definition);
    compiler.compile(function_call);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_functions, RecursiveFunction) {
    // (define (sum n) (if (= n 1) 1 (+ n (sum (- n 1)))))
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "sum"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "n")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "if"),
                            {
                                    new SyntaxTreeNode(
                                            new Token(Token::Symbol, "="),
                                            {
                                                    new SyntaxTreeNode(new Token(Token::Symbol, "n")),
                                                    new SyntaxTreeNode(new Token(1)),
                                            }),
                                    new SyntaxTreeNode(new Token(1)),
                                    new SyntaxTreeNode(
                                            new Token(Token::Symbol, "+"),
                                            {
                                                    new SyntaxTreeNode(new Token(Token::Symbol, "n")),
                                                    new SyntaxTreeNode(
                                                            new Token(Token::Symbol, "sum"),
                                                            {
                                                                    new SyntaxTreeNode(
                                                                            new Token(Token::Symbol, "-"),
                                                                            {
                                                                                    new SyntaxTreeNode(new Token(Token::Symbol, "n")),
                                                                                    new SyntaxTreeNode(new Token(1)),
                                                                            }),
                                                            }),
                                            }),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({}),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new LoadLiteral(1),
                            new Equals(),
                            new CondJumpIfNot(6),
                            new LoadLiteral(1),
                            new Jump(12),
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(0)),
                            new LoadLiteral(1),
                            new Subtract(),
                            new Call(1, 1),
                            new Add(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_functions, MultipleFunctionsDefinitions) {
    const auto first_function = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "square-area"),
                            {new SyntaxTreeNode(new Token(Token::Symbol, "x"))}),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                            }),
            });

    const auto second_function = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "rect-area"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                            }),
            });

    const auto expected_result = Program(
            {
                    new Segment({}),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(0)),
                            new Multiply(),
                    }),
                    new Segment({
                            new Load(new LocalRegister(0)),
                            new Load(new LocalRegister(1)),
                            new Multiply(),
                    }),
            });

    auto compiler = Compiler();
    compiler.compile(first_function);
    compiler.compile(second_function);

    EXPECT_EQ(expected_result == compiler.program, true);
}
