#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Not.h"
#include "lexer/Token.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_not, ShouldCompileNotInstruction) {
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "not"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "="),
                            {
                                    new SyntaxTreeNode(Token(5)),
                                    new SyntaxTreeNode(Token(4)),
                            }),
            });

    const auto expected_result = Program({
            new Segment(
                    {
                            new LoadLiteral(5),
                            new LoadLiteral(4),
                            new Equals(),
                            new Not(),
                    }),
    });

    Compiler compiler;
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}