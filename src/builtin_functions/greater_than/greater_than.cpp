#include "greater_than.h"
#include "eval/eval.h"
#include "parser/SyntaxTreeNode.h"
#include <string>
#include <vector>

inline bool isGreaterThan(Token token1, Token token2) {
    if (token1.type == Token::Decimal || token2.type == Token::Decimal)
        return std::stof(token1.token) > std::stof(token2.token);
    else
        return std::stoi(token1.token) > std::stoi(token2.token);
}

SyntaxTreeNode GreaterThan::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!isGreaterThan(Evaluate::evaluate(args[i - 1]).token,
                           Evaluate::evaluate(args[i]).token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
