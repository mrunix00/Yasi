#pragma once

#include "lexer/Lexer.h"
#include <utility>
#include <vector>

class SyntaxTreeNode {
public:
    Token token;
    std::vector<SyntaxTreeNode *> children;

    SyntaxTreeNode() = default;
    SyntaxTreeNode(Token token, const std::vector<SyntaxTreeNode *> &children)
        : token(std::move(token)), children(children) {}

    ~SyntaxTreeNode() {
        for (auto child: children)
            delete child;
    }

    explicit SyntaxTreeNode(Token token) : token(std::move(token)) {}

    bool operator==(const SyntaxTreeNode &node) const {
        if (token == node.token) {
            for (auto i = 0; i < children.size(); i++) {
                auto child1 = node.children[i];
                if (auto child2 = children[i]; *child1 != *child2)
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

