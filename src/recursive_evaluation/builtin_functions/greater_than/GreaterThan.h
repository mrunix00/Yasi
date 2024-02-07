#pragma once

#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/builtin_functions/Function.h"
#include <string>
#include <vector>

namespace RecursiveEvaluation {
    class GreaterThan final : public Function {
    public:
        const std::string &getName() override {
            static const std::string name = ">";
            return name;
        };
        SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
    };
}// namespace RecursiveEvaluation
