#ifndef YASI_FUNCTION_H
#define YASI_FUNCTION_H

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

#endif
