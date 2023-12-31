#ifndef YASI_COND_HH
#define YASI_COND_HH

#include "recursive_evaluation/builtin_functions/Function.h"

namespace RecursiveEvaluation {
    class Cond : public Function {
    public:
        const std::string &getName() override {
            static const std::string name = "cond";
            return name;
        };
        SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
    };
}

#endif
