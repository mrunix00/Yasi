#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_variables, GlobalVariableDefinition) {
    // (define x 10)
    const auto expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(10)),
            });

    const auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new Store(new GlobalRegister(0)),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_variables, MultipleGlobalVariablesDefinitions) {
    // (define x 10)
    const auto first_expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(10)),
            });
    const auto second_expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "y")),
                    new SyntaxTreeNode(Token(15)),
            });

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new Store(new GlobalRegister(0)),
                    new LoadLiteral(15),
                    new Store(new GlobalRegister(1)),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}

TEST(compiler_variables, UseGlobalVariableInAnExpression) {
    // (define x 10)
    const auto first_expression = SyntaxTreeNode(
            Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(Token(10)),
            });
    const auto second_expression = SyntaxTreeNode(
            Token(Token::Symbol, "x"));

    auto expected_result = Program({
            new Segment({
                    new LoadLiteral(10),
                    new Store(new GlobalRegister(0)),
                    new Load(new GlobalRegister(0)),
            }),
    });

    auto compiler = Compiler();
    compiler.compile(first_expression);
    compiler.compile(second_expression);

    EXPECT_EQ(expected_result == compiler.program, true);
}
