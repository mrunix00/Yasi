#include <stack>
#include <queue>
#include <map>
#include "parse.h"
#include "SyntaxTreeNode.h"

SyntaxTreeNode parse(const std::vector<Token> &tokens) {
    Token operation;
    std::stack<Token> operators_stack;
    std::stack<std::vector<SyntaxTreeNode>> nodes_stack;

    for (const auto &token: tokens) {
        if (token.type == Token::OpenBracket
            || operators_stack.top().type == Token::OpenBracket) {
            if (token.type == Token::OpenBracket) nodes_stack.emplace();
            operators_stack.push(token);
        } else if (token.type != Token::ClosedBracket) {
            nodes_stack.top().emplace_back(token);
        } else {
            auto args = nodes_stack.top();
            nodes_stack.pop();
            if (nodes_stack.empty()) nodes_stack.emplace();
            nodes_stack.top().emplace_back(
                    operators_stack.top(),
                    args
            );
            operators_stack.pop();
            operators_stack.pop();
        }
    }

    return nodes_stack.top().front();
}