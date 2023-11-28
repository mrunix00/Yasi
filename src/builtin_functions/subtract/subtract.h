#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "../../parser/SyntaxTreeNode.h"
#include "../Function.h"

class Subtract : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) override;
};

#endif
