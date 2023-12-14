#include "Equals.h"
#include "evaluation/Evaluate.h"

SyntaxTreeNode Equals::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 1; i < args.size(); i++)
        if (!(Evaluate::evaluate(args[i]).token ==
            Evaluate::evaluate(args[i - 1]).token))
            return {Token(Token::Boolean, "#f")};
    return {Token(Token::Boolean, "#t")};
}
