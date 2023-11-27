#ifndef DUMMYLISP_MULTIPLY_H
#define DUMMYLISP_MULTIPLY_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Multiply : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) override;
};

#endif
