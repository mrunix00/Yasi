#ifndef YASI_EVALUATE_H
#define YASI_EVALUATE_H

#include "../parser/SyntaxTreeNode.h"

class Evaluate {
public:
    static SyntaxTreeNode evaluate(const SyntaxTreeNode &tree);
};

#endif
