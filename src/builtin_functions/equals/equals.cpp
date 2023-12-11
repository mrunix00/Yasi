#include "equals.h"

inline bool equals(Token token1, Token token2) {
    if (token1.type == Token::Decimal || token2.type == Token::Decimal)
        return std::stof(token1.token) == std::stof(token2.token);
    else
        return std::stoi(token1.token) == std::stoi(token2.token);
}

SyntaxTreeNode Equals::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!equals(args[i].token, args[i - 1].token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
