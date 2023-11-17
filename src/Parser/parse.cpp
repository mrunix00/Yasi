#include "parse.h"

AbstractSyntaxTree parse(const std::vector<Token> &tokens) {
    Token operation;
    std::vector<Argument> arguments;

    for (const auto &token: tokens) {
        if (token.type == Token::Symbol) {
            operation = token;
        }
        if (token.type == Token::Integer || token.type == Token::String) {
            arguments.emplace_back(token);
        }
    }

    return AbstractSyntaxTree(operation, arguments);
}