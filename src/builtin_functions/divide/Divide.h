#ifndef YASI_DIVIDE_H
#define YASI_DIVIDE_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Divide : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) override;
};


#endif
