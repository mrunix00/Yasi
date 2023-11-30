#include "Parser.h"
#include <stack>

SyntaxTreeNode Parser::parse(const std::vector<Token> &tokens) {
    std::stack<Token> operators_stack;
    std::stack<std::vector<SyntaxTreeNode>> nodes_stack;

    for (const auto &token: tokens) {
        if (token.type == Token::OpenBracket) {
            nodes_stack.emplace();
            operators_stack.push(token);
        } else if (operators_stack.top().type == Token::OpenBracket) {
            operators_stack.push(token);
        } else if (token.type == Token::ClosedBracket) {
            auto args = nodes_stack.top();
            nodes_stack.pop();
            if (nodes_stack.empty())
                nodes_stack.emplace();
            nodes_stack.top().emplace_back(operators_stack.top(), args);
            operators_stack.pop();// pop the operator
            operators_stack.pop();// pop the bracket
        } else {
            nodes_stack.top().emplace_back(token);
        }
    }

    return nodes_stack.top().front();
}