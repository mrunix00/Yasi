#include "equals.h"
#include "eval/eval.h"

inline bool equals(Token token1, Token token2) {
    return token1.asDecimal() == token2.asDecimal();
}

SyntaxTreeNode Equals::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!equals(Evaluate::evaluate(args[i]).token,
                    Evaluate::evaluate(args[i - 1]).token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
