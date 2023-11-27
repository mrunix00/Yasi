#ifndef DUMMYLISP_DIVIDE_H
#define DUMMYLISP_DIVIDE_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Divide : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) override;
};


#endif
