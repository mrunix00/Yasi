#ifndef YASI_SYNTAXTREENODE_H
#define YASI_SYNTAXTREENODE_H

#include "lexer/Lexer.h"
#include <vector>

class SyntaxTreeNode {
public:
    Token *token;
    std::vector<SyntaxTreeNode *> children;

    SyntaxTreeNode() : token(new Token()){};
    SyntaxTreeNode(Token *token, const std::vector<SyntaxTreeNode *> &children)
        : token(token), children(children) {}

    explicit SyntaxTreeNode(Token *token) : token(token) {}

    bool operator==(const SyntaxTreeNode &node) const {
        if (*token == *node.token) {
            for (auto i = 0; i < children.size(); i++) {
                auto child1 = *node.children[i];
                if (auto child2 = *children[i]; child1 != child2)
                    return false;
            }
            return true;
        }
        return false;
    }

    bool operator!=(const SyntaxTreeNode &node) const {
        return !operator==(node);
    }
};

#endif
