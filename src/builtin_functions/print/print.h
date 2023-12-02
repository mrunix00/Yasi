#include "builtin_functions/Function.h"

class Print : public Function {
public:
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};
