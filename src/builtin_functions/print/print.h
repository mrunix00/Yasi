#include "builtin_functions/Function.h"
#include <string>

class Print : public Function {
public:
    const std::string &getName() override {
        static const std::string name = "print" ;
        return name;
    };
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};
