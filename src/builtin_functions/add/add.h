#ifndef DUMMYLISP_ADD_H
#define DUMMYLISP_ADD_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Add : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) override;
};

#endif
