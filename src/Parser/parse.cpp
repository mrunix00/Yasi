#include <stack>
#include <queue>
#include "parse.h"
#include "SyntaxTreeNode.h"

SyntaxTreeNode parse(const std::vector<Token> &tokens) {
    Token operation;
    std::vector<SyntaxTreeNode> arguments;

    std::stack<Token> brackets_stack;
    std::vector<Token> current_expression;

    for (const auto &token: tokens) {
        if (token.type == Token::OpenBracket) {
            brackets_stack.push(token);
            current_expression.clear();
        } else if (token.type == Token::ClosedBracket) {
            if (brackets_stack.size() > 1) {
                auto l = parse(current_expression);
                arguments.emplace_back(l.token, l.children);
            }
            brackets_stack.pop();
        } else if (token.type == Token::Symbol) {
            if (brackets_stack.size() == 1) operation = token;
        } else if (token.type == Token::Integer || token.type == Token::String) {
            if (brackets_stack.size() == 1) arguments.emplace_back(token);
        }
        current_expression.push_back(token);
    }

    return {operation, arguments};
}