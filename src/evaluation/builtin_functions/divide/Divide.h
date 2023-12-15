#ifndef YASI_DIVIDE_H
#define YASI_DIVIDE_H

#include "evaluation/builtin_functions/Function.h"
#include "parser/SyntaxTreeNode.h"

class Divide : public Function {
public:
    const std::string &getName() override {
        static const std::string name = "/";
        return name;
    };
    SyntaxTreeNode *evaluate(const std::vector<SyntaxTreeNode *> &args) override;
};

#endif
