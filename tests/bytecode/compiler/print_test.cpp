#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/SendToStdout.h"
#include "lexer/Token.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_print, SimplePrintStatement) {
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(Token(12)),
            });

    const auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(12),
                            new SendToStdout(),
                            new LoadLiteral("\n"),
                            new SendToStdout(),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_print, PrintMultipleArgs) {
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(Token(75)),
                    new SyntaxTreeNode(Token(12)),
            });

    const auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(75),
                            new SendToStdout(),
                            new LoadLiteral(12),
                            new SendToStdout(),
                            new LoadLiteral("\n"),
                            new SendToStdout(),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_print, PrintStrings) {
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(Token(Token::String, "Hello World!")),
            });

    const auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral("Hello World!"),
                            new SendToStdout(),
                            new LoadLiteral("\n"),
                            new SendToStdout(),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
