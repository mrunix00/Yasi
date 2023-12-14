#include "Cond.h"
#include "evaluation/Evaluate.h"

SyntaxTreeNode Cond::evaluate(const std::vector<SyntaxTreeNode> &args) {
    for (int i = 0; i < args.size(); i += 2) {
        auto condition = Evaluate::evaluate(args[i]);
        if (condition.token == Token(Token::Boolean, "#t"))
            return Evaluate::evaluate(args[i + 1]);
    }
    if (args.size() % 2) {
        return Evaluate::evaluate(args[args.size() - 1]);
    }
    return {};
}
