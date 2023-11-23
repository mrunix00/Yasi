#include "eval.h"

SyntaxTreeNode evaluate(const SyntaxTreeNode &tree) {
    if (tree.token == Token(Token::Symbol, "+")) {
        int result = 0;

        for (const auto &operand: tree.children) {
            result += atoi(operand.token.token.c_str());
        }

        return SyntaxTreeNode(
                Token(
                        Token::Integer,
                        std::to_string(result)
                )
        );
    } else if (tree.token == Token(Token::Symbol, "*")) {
        int result = 1;

        for (const auto &operand: tree.children) {
            result *= atoi(operand.token.token.c_str());
        }

        return SyntaxTreeNode(
                Token(
                        Token::Integer,
                        std::to_string(result)
                )
        );
    } else if (tree.token == Token(Token::Symbol, "-")) {
        int result = atoi(tree.children[0].token.token.c_str());

        for (int i = 1; i < tree.children.size(); i++) {
            auto operand = tree.children[i].token.token;
            result -= atoi(operand.c_str());
        }

        return SyntaxTreeNode(
                Token(
                        Token::Integer,
                        std::to_string(result)
                )
        );
    }
}