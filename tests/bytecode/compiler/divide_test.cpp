#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Divide.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_divide, CompileSimpleDivision) {
    // (/ 12 74)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "/"),
            {
                    new SyntaxTreeNode(Token(12)),
                    new SyntaxTreeNode(Token(74)),
            });

    const auto expected_result = Program({
            new Segment({
                    new LoadLiteral(12),
                    new LoadLiteral(74),
                    new Divide(),
            }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_divide, CompileLongDivision) {
    // (/ 12 74 17)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "/"),
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
                            new Divide(),
                            new LoadLiteral(17),
                            new Divide(),
                    }),
            });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_divide, CompileNestedDivision) {
    // (/ (/ 23 74) 43)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "/"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "/"),
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
                            new Divide(),
                            new LoadLiteral(43),
                            new Divide(),
                    }),
            });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
