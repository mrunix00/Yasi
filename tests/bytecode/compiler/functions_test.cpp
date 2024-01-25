#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Load.h"
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

    std::vector<Segment *> expected_result = {
            new Segment({}),
            new Segment({
                    new Load(0),
                    new Load(0),
                    new Multiply(),
            }),
    };

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result.size(), compiler.program_segments.size());
    for (int i = 0; i < compiler.program_segments.size(); i++) {
        EXPECT_EQ(*compiler.program_segments[i], *expected_result[i]);
    }
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

    std::vector<Segment *> expected_result = {
            new Segment({}),
            new Segment({
                    new Load(0),
                    new Load(1),
                    new Add(),
            }),
    };

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result.size(), compiler.program_segments.size());
    for (int i = 0; i < compiler.program_segments.size(); i++) {
        EXPECT_EQ(*compiler.program_segments[i], *expected_result[i]);
    }
}