#ifndef YASI_SYNTAXTREENODE_H
#define YASI_SYNTAXTREENODE_H

#include "lexer/Lexer.h"
#include <utility>
#include <vector>

class SyntaxTreeNode {
public:
    Token token;
    std::vector<SyntaxTreeNode> children;

    SyntaxTreeNode() {};
    SyntaxTreeNode(Token token, const std::vector<SyntaxTreeNode> &children)
        : token(std::move(token)), children(children) {}

    explicit SyntaxTreeNode(Token token) : token(std::move(token)) {}

    bool operator==(const SyntaxTreeNode &node) const {
        return token == node.token && children == node.children;
    }
};

#endif
