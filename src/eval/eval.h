#ifndef YASI_EVAL_H
#define YASI_EVAL_H

#include "../parser/SyntaxTreeNode.h"

class Evaluate {
public:
    static SyntaxTreeNode evaluate(const SyntaxTreeNode &tree);
};

#endif
