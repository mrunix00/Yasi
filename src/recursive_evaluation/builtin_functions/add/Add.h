#ifndef YASI_ADD_H
#define YASI_ADD_H

#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/builtin_functions/Function.h"

namespace RecursiveEvaluation {
    class Add : public Function {
    public:
        const std::string &getName() override {
            static const std::string name = "+";
            return name;
        };
        SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
    };
}

#endif
