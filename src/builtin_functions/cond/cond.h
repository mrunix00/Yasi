#ifndef YASI_COND_HH
#define YASI_COND_HH

#include "builtin_functions/Function.h"

class Cond : public Function {
public:
    std::string getName() override { return "cond"; }
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};

#endif
