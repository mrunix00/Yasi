#ifndef DUMMYLISP_EVAL_H
#define DUMMYLISP_EVAL_H

#include "../parser/SyntaxTreeNode.h"

namespace Evaluate {
    SyntaxTreeNode evaluate(const SyntaxTreeNode &tree);
}

#endif
