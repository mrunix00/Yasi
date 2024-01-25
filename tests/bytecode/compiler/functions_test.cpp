#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
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
            {{"square", 1}},
            {{"x", 0}},
            {
                    new Segment({}),
                    new Segment({
                            new Load(0),
                            new Load(0),
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

    auto expected_result = Program(
            {{"add", 1}},
            {{"x", 0}, {"y", 1}},
            {
                    new Segment({}),
                    new Segment({
                            new Load(0),
                            new Load(1),
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

    auto expected_result = Program(
            {{"square", 1}},
            {{"x", 0}},
            {
                    new Segment({
                            new LoadLiteral(15),
                            new Call(1),
                    }),
                    new Segment({
                            new Load(0),
                            new Load(0),
                            new Multiply(),
                    }),
            });

    Compiler compiler = Compiler();
    compiler.compile(function_definition);
    compiler.compile(function_call);

    EXPECT_EQ(expected_result == compiler.program, true);
}
