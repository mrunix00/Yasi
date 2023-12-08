#ifndef YASI_FUNCTION_H
#define YASI_FUNCTION_H

#include "../parser/SyntaxTreeNode.h"
#include <string>

class Function {
public:
    virtual std::string getName() = 0;
    virtual ~Function() = default;
    virtual SyntaxTreeNode evaluate(
            const std::vector<SyntaxTreeNode> &args) = 0;
};

#endif
