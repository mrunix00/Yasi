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
    };
    Type type = None;
    virtual void compile(Bytecode::Segment *, Bytecode::Program &,
                         std::vector<Bytecode::Instruction *> &) {}
    virtual ~SyntaxTreeNode() = default;
    virtual bool operator==(const SyntaxTreeNode &op) const = 0;
};

class TokenNode final : public SyntaxTreeNode {
    Token token;

public:
    explicit TokenNode(Token token) : token(std::move(token)) {
        type = Type::TokenNode;
    }

    [[nodiscard]] std::string getName() const { return token.token; }
    [[nodiscard]] Token::TokenType getType() const { return token.type; }

    void compile(Bytecode::Segment *segment, Bytecode::Program &program,
                 std::vector<Bytecode::Instruction *> &instructions) override;

    bool operator==(const SyntaxTreeNode &op) const override {
        return type == op.type &&
               ((TokenNode *) &op)->token == token;
    }
};

class Expression : public SyntaxTreeNode {
    Token function;
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

    bool operator==(const SyntaxTreeNode &op) const override {
        if (type != op.type || !(((Expression *) &op)->function == function) ||
            ((Expression *) &op)->args.size() != args.size())
            return false;

        for (auto i = 0; i < args.size(); i++) {
            if (!(*args[i] == *((Expression *) &op)->args[i]))
                return false;
        }

        return true;
    }
};