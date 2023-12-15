#ifndef YASI_PARSER_H
#define YASI_PARSER_H

#include "SyntaxTreeNode.h"

class Parser {
public:
    static SyntaxTreeNode* parse(const std::vector<Token*> &tokens);
};

#endif
