#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/StoreGlobal.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_variables, GlobalVariableDefinition) {
    // (define x 10)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(10)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new StoreGlobal(0),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_variables, MultipleGlobalVariablesDefinitions) {
    // (define x 10)
    const auto first_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(10)),
            });
    const auto second_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "y")),
                    new SyntaxTreeNode(new Token(15)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new StoreGlobal(0),
                    new LoadLiteral(15),
                    new StoreGlobal(1),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_variables, UseGlobalVariableInAnExpression) {
    // (define x 10)
    const auto first_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(10)),
            });
    const auto second_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "x"));

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new StoreGlobal(0),
                    new LoadGlobal(0),
            }),
    });

    Compiler compiler = Compiler();
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
