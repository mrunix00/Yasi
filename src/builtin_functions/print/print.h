#include "builtin_functions/Function.h"
#include <string>

class Print : public Function {
public:
    std::string getName() override { return "print"; };
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};
