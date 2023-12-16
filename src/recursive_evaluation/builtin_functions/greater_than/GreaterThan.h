#ifndef YASI_GREATER_THAN_HH
#define YASI_GREATER_THAN_HH

#include "recursive_evaluation/builtin_functions/Function.h"
#include "parser/SyntaxTreeNode.h"
#include <string>
#include <vector>

class GreaterThan : public Function {
public:
    const std::string &getName() override {
        static const std::string name = ">";
        return name;
    };
    SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
};

#endif
