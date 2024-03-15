#pragma once

#include "SyntaxTreeNode.h"

SyntaxTreeNode *parse(const std::vector<Token *> &tokens);
