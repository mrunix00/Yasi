#include <utility>

#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/RecursiveEvaluation.h"
#include "recursive_evaluation/builtin_functions/Function.h"

namespace RecursiveEvaluation {
    class Variable : public RecursiveEvaluation::Function {
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

    class DefinedFunction : public RecursiveEvaluation::Function {
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

    class Define : public RecursiveEvaluation::Function {
    public:
        const std::string &getName() override {
            static const std::string name = "define";
            return name;
        };
        SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
    };
}// namespace RecursiveEvaluation
