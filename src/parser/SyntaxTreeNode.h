#pragma once

#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "lexer/Lexer.h"
#include <utility>
#include <vector>

class SyntaxTreeNode {
public:
    enum Type {
        None,
        TokenNode,
        Expression,
        CondExpression,
        LambdaExpression,
    };
    Type type = None;
    virtual void compile(Bytecode::Segment *, Bytecode::Program &,
                         std::vector<Bytecode::Instruction *> &) = 0;
    void compile(Bytecode::Program &program) {
        compile(program.segments[0], program, program.segments[0]->instructions);
    }
    virtual ~SyntaxTreeNode() = default;
    virtual bool operator==(const SyntaxTreeNode &op) const = 0;
};

class TokenNode final : public SyntaxTreeNode {

public:
    explicit TokenNode(Token token) : token(std::move(token)) {
        type = Type::TokenNode;
    }

    [[nodiscard]] std::string getName() const { return token.token; }

    void compile(Bytecode::Segment *segment, Bytecode::Program &program,
                 std::vector<Bytecode::Instruction *> &instructions) override;

    bool operator==(const SyntaxTreeNode &op) const override;
    Token token;
};

class Expression : public SyntaxTreeNode {
    std::vector<SyntaxTreeNode *> args;

public:
    Expression(Token function, std::vector<SyntaxTreeNode *> args)
        : function(std::move(function)), args(std::move(args)) {
        type = TokenNode::Expression;
    }

    [[nodiscard]] std::string getName() const { return function.token; }
    std::vector<SyntaxTreeNode *> getArgs() { return args; }

    void compile(Bytecode::Segment *segment, Bytecode::Program &program,
                 std::vector<Bytecode::Instruction *> &instructions) override;

    bool operator==(const SyntaxTreeNode &op) const override;
    Token function;
};

class CondExpression final : public SyntaxTreeNode {
    // This is a cursed way to organize this part of code
    // TODO: refactor this piece of shit
public:
    struct Case {
        SyntaxTreeNode *condition;
        SyntaxTreeNode *result;
    };

private:
    std::vector<Case> cases;
    SyntaxTreeNode *default_case;

public:
    CondExpression(std::vector<Case> cases,
                   SyntaxTreeNode *default_case)
        : cases(std::move(cases)), default_case(default_case) {
        type = Type::CondExpression;
    }

    void compile(Bytecode::Segment *segment, Bytecode::Program &program,
                 std::vector<Bytecode::Instruction *> &instructions) override;

    bool operator==(const SyntaxTreeNode &op) const override;
};

class LambdaExpression final : public SyntaxTreeNode {
    std::vector<SyntaxTreeNode *> args;
    SyntaxTreeNode *definition;

public:
    LambdaExpression(std::vector<SyntaxTreeNode *> args,
                     SyntaxTreeNode *definition);
    void compile(Bytecode::Segment *segment, Bytecode::Program &program,
                 std::vector<Bytecode::Instruction *> &instructions) override;

    bool operator==(const SyntaxTreeNode &op) const override;
};
