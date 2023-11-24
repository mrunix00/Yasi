#ifndef DUMMYLISP_ADD_H
#define DUMMYLISP_ADD_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Add : public Function {
public:
    explicit Add(const std::vector<SyntaxTreeNode> &args)
            : Function(args) {
    }

    SyntaxTreeNode evaluate() override;
};

#endif
