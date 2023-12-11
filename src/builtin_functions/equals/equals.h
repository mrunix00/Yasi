#ifndef YASI_EQUALS_HH
#define YASI_EQUALS_HH

#include "builtin_functions/Function.h"
#include "parser/SyntaxTreeNode.h"
#include <string>
#include <vector>

class Equals : public Function {
public:
    std::string getName() override { return "="; }
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};

#endif
