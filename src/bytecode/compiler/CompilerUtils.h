#pragma once
#include "parser/SyntaxTreeNode.h"
#include <algorithm>
#include <vector>

namespace Bytecode {
    inline bool is_optimizable(const std::vector<SyntaxTreeNode *> &args) {
        return std::all_of(args.begin(), args.end(), [](const SyntaxTreeNode *arg) {
            if (!arg->children.empty()) {
                if (!is_optimizable(arg->children)) return false;
            } else {
                return arg->token->type != Token::Symbol;
            }
            return true;
        });
    }
}// namespace Bytecode