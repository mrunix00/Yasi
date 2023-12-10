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
            override {
        auto result = Evaluate::evaluate(value);
        value = result;
        return value;
    };
};

class DefinedFunction : public Function {
    std::string name;
    SyntaxTreeNode definition;
    std::vector<SyntaxTreeNode> arguments;

public:
    DefinedFunction(
            std::string name,
            std::vector<SyntaxTreeNode> args,
            SyntaxTreeNode definition)
        : name(name),
          arguments(args),
          definition(definition) {}
    std::string getName() override { return name; }
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};

class Define : public Function {
public:
    std::string getName() override { return "define"; };
    SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode> &args) override;
};
