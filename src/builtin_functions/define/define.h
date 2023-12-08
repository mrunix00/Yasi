#include "builtin_functions/Function.h"
#include "eval/eval.h"
#include "parser/SyntaxTreeNode.h"

class Variable : public Function {
    std::string name;
    SyntaxTreeNode value;

public:
    Variable(std::string name, SyntaxTreeNode value)
        : name(name), value(value) {}
    std::string getName() override { return name; }
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args)
            override { return Evaluate::evaluate(value); };
};

class Define : public Function {
public:
    std::string getName() override { return "define"; };
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};
