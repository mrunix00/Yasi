#ifndef DUMMYLISP_SYNTAXTREENODE_H
#define DUMMYLISP_SYNTAXTREENODE_H

#include <utility>
#include <vector>
#include "../Tokens/Token.h"

class SyntaxTreeNode {
public:
    Token token;
    std::vector<SyntaxTreeNode> children;

    SyntaxTreeNode(
            Token token,
            const std::vector<SyntaxTreeNode> &children
    ) : token(std::move(token)),
        children(children) {}

    explicit SyntaxTreeNode(Token token) : token(std::move(token)) {}

    bool operator==(const SyntaxTreeNode &argument) const {
        return token == argument.token && children == argument.children;
    }
};

#endif //DUMMYLISP_SYNTAXTREENODE_H
