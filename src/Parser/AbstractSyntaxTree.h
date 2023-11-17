#ifndef DUMMYLISP_ABSTRACTSYNTAXTREE_H
#define DUMMYLISP_ABSTRACTSYNTAXTREE_H

#include "../Tokens/Token.h"
#include <utility>
#include <vector>

class Argument {
    Token token;
public:
    explicit Argument(Token token) : token(std::move(token)) {};

    bool operator==(const Argument &argument) const {
        return argument.token == token;
    }
};

class AbstractSyntaxTree {
public:
    Token operation;
    std::vector<Argument> arguments;

    explicit AbstractSyntaxTree(
            Token operation,
            const std::vector<Argument> &arguments
    ) : operation(std::move(operation)),
        arguments(arguments) {}

    bool operator==(const AbstractSyntaxTree &tree) const {
        return tree.operation == operation
               && arguments == tree.arguments;
    }
};


#endif
