#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "parser/SyntaxTreeNode.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(compiler_variables, VariableDefinition) {
    // (define x 10)
    const auto expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(10)),
            });

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(10),
            new Store(0),
    };

    std::vector<Instruction *> actual_result;
    Compiler().compile(expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_variables, MultipleVariablesDefinitions) {
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

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(10),
            new Store(0),
            new LoadLiteral(15),
            new Store(1),
    };

    std::vector<Instruction *> actual_result;
    Compiler compiler;
    compiler.compile(first_expression, actual_result);
    compiler.compile(second_expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}

TEST(compiler_variables, UseVariableInAnExpression) {
    // (define x 10)
    const auto first_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "define"),
            {
                    new SyntaxTreeNode(new Token(Token::Symbol, "x")),
                    new SyntaxTreeNode(new Token(10)),
            });
    const auto second_expression = SyntaxTreeNode(
            new Token(Token::Symbol, "x"));

    const std::vector<Instruction *> expected_result = {
            new LoadLiteral(10),
            new Store(0),
            new Load(0),
    };

    std::vector<Instruction *> actual_result;
    Compiler compiler;
    compiler.compile(first_expression, actual_result);
    compiler.compile(second_expression, actual_result);

    EXPECT_EQ(expected_result.size(), actual_result.size());
    for (int i = 0; i < actual_result.size(); i++) {
        EXPECT_EQ(*actual_result[i], *expected_result[i]);
    }
}
