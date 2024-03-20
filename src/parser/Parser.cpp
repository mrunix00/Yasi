#include "Parser.h"
#include "exceptions/SyntaxError.h"
#include <stack>

SyntaxTreeNode *parse(const std::vector<Token *> &tokens) {
    std::stack<Token> operators_stack;
    std::stack<std::vector<SyntaxTreeNode *>> nodes_stack;

    if (tokens.size() == 1) return new TokenNode(*tokens[0]);

    for (const auto &token: tokens) {
        if (token->type == Token::OpenBracket) {
            nodes_stack.emplace();
            operators_stack.push(*token);
        } else if (!operators_stack.empty() &&
                   operators_stack.top().type == Token::OpenBracket) {
            if (token->type == Token::ClosedBracket) {
                throw SyntaxError(
                        "An atom was expected after the opening "
                        "parenthesis but not found",
                        operators_stack.top().line,
                        operators_stack.top().column);
            }
            operators_stack.push(*token);
        } else if (token->type == Token::ClosedBracket) {
            if (operators_stack.empty()) {
                throw SyntaxError("Unexpected parenthesis -> ')'",
                                  token->line, token->column);
            }
            auto args = nodes_stack.top();
            nodes_stack.pop();
            if (nodes_stack.empty())
                nodes_stack.emplace();
            if (operators_stack.top().token == "cond") {
                std::vector<CondExpression::Case> cases;
                SyntaxTreeNode *default_case = nullptr;
                for (auto arg: args) {
                    auto expression = (Expression *) arg;
                    if (expression->function.token == "else") {
                        default_case = expression->getArgs()[0];
                        continue;
                    }
                    cases.push_back({
                            expression->getArgs()[0],
                            new TokenNode(expression->function),
                    });
                }
                nodes_stack.top().emplace_back(
                        new CondExpression(cases, default_case));
            } else if (operators_stack.top().token == "lambda" ||
                       operators_stack.top().token == "λ") {
                std::vector<SyntaxTreeNode *> arguments;
                arguments.push_back(new TokenNode(((Expression *) args[0])->function));
                for (auto arg: ((Expression *) args[0])->getArgs())
                    arguments.push_back((TokenNode *) arg);
                nodes_stack.top().emplace_back(
                        new LambdaExpression(
                                arguments,
                                args.back()));
            } else {
                nodes_stack.top().emplace_back(
                        new Expression(operators_stack.top(), args));
            }
            operators_stack.pop();// pop the operator
            operators_stack.pop();// pop the bracket
        } else {
            nodes_stack.top().emplace_back(new TokenNode(*token));
        }
    }

    if (nodes_stack.empty()) return nullptr;
    return nodes_stack.top().front();
}
