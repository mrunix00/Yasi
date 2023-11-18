#ifndef DUMMYLISP_ABSTRACTSYNTAXTREE_H
#define DUMMYLISP_ABSTRACTSYNTAXTREE_H

#include "../Tokens/Token.h"
#include "Argument.h"
#include <utility>
#include <vector>

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
