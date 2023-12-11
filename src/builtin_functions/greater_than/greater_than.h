#ifndef YASI_GREATER_THAN_HH
#define YASI_GREATER_THAN_HH

#include "builtin_functions/Function.h"
#include "parser/SyntaxTreeNode.h"
#include <string>
#include <vector>

class GreaterThan : public Function {
public:
    std::string getName() override { return ">"; }
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};

#endif
