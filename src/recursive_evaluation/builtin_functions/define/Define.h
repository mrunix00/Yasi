#include <utility>

#include "recursive_evaluation/Evaluate.h"
#include "recursive_evaluation/builtin_functions/Function.h"
#include "parser/SyntaxTreeNode.h"

class Variable : public Function {
    std::string *name;
    SyntaxTreeNode *value;

public:
    Variable(std::string *name,
             SyntaxTreeNode *value)
        : name(name),
          value(value) {}
    const std::string &getName() override { return *name; }
    SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args)
            override { return value; };
};

class DefinedFunction : public Function {
    std::string *name;
    SyntaxTreeNode *definition;
    std::vector<SyntaxTreeNode *> arguments;

public:
    DefinedFunction(
            std::string *name,
            std::vector<SyntaxTreeNode *> args,
            SyntaxTreeNode *definition)
        : name(name),
          arguments(std::move(args)),
          definition(definition) {}
    const std::string &getName() override { return *name; }
    SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
};

class Define : public Function {
public:
    const std::string &getName() override {
        static const std::string name = "define";
        return name;
    };
    SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
};
