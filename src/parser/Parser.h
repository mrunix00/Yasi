#pragma once

#include "SyntaxTreeNode.h"

class Parser {
public:
    static SyntaxTreeNode *parse(const std::vector<Token *> &tokens);
};
