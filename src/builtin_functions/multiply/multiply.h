#ifndef DUMMYLISP_MULTIPLY_H
#define DUMMYLISP_MULTIPLY_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Multiply : public Function {
public:
    explicit Multiply(const std::vector<SyntaxTreeNode> &args)
            : Function(args) {
    }

    SyntaxTreeNode evaluate() override;
};

#endif
