#include "LessThan.h"
#include "evaluation/Evaluate.h"

inline bool isLessThan(Token token1, Token token2) {
    return token1.asDecimal() < token2.asDecimal();
}

SyntaxTreeNode LessThan::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!isLessThan(Evaluate::evaluate(args[i - 1]).token,
                        Evaluate::evaluate(args[i]).token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
