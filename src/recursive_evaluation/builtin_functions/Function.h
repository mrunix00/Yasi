#pragma once

#include "parser/SyntaxTreeNode.h"
#include <string>

namespace RecursiveEvaluation {
    class Function {
    public:
        virtual const std::string& getName() = 0;
        virtual ~Function() = default;
        virtual SyntaxTreeNode* evaluate(
                const std::vector<SyntaxTreeNode*> &args) = 0;
    };
}
