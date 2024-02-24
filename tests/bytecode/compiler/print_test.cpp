#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/objects/StdOutRegister.h"
#include "bytecode/objects/StringLiteral.h"
#include "lexer/Token.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_print, SimplePrintStatement) {
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(new Token(12)),
            });

    auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(12),
                            new Store(new StdOutRegister()),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_print, PrintMultipleArgs) {
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(new Token(75)),
                    new SyntaxTreeNode(new Token(12)),
            });

    auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(75),
                            new Store(new StdOutRegister()),
                            new LoadLiteral(12),
                            new Store(new StdOutRegister()),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_print, PrintStrings) {
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "print"),
            {
                    new SyntaxTreeNode(new Token(Token::String, "Hello World!")),
            });

    auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(new StringLiteral("Hello World!")),
                            new Store(new StdOutRegister()),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
