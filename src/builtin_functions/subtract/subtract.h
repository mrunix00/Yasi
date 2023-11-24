#ifndef DUMMYLISP_SUBTRACT_H
#define DUMMYLISP_SUBTRACT_H

#include "../../parser/SyntaxTreeNode.h"
#include "builtin_functions/Function.h"

class Subtract : public Function {
public:
    explicit Subtract(const std::vector<SyntaxTreeNode> &args)
            : Function(args) {
    }

    SyntaxTreeNode evaluate() override;
};

#endif
