#include "bytecode/compiler/Compiler.h"
#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/objects/StdOutRegister.h"
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