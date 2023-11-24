#ifndef DUMMYLISP_FUNCTION_H
#define DUMMYLISP_FUNCTION_H

#include <utility>
#include <vector>
#include "parser/SyntaxTreeNode.h"

class Function {
protected:
    std::vector<SyntaxTreeNode> args;

    explicit Function(std::vector<SyntaxTreeNode> args)
            : args(std::move(args)) {}
public:
    virtual SyntaxTreeNode evaluate() = 0;
};

#endif
