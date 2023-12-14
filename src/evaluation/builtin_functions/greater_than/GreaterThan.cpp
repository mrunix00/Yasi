#include "GreaterThan.h"
#include "evaluation/Evaluate.h"
#include "parser/SyntaxTreeNode.h"
#include <vector>

inline bool isGreaterThan(Token token1, Token token2) {
    return token1.asDecimal() > token2.asDecimal();
}

SyntaxTreeNode GreaterThan::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!isGreaterThan(Evaluate::evaluate(args[i - 1]).token,
                           Evaluate::evaluate(args[i]).token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
