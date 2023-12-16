#include "Cond.h"
#include "recursive_evaluation/Evaluate.h"

static Token *True = new Token(Token::Boolean, new std::string("#t"));

SyntaxTreeNode *Cond::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    for (int i = 0; i < args.size(); i += 2) {
        auto condition = *Evaluate::evaluate(args[i]);
        if (*condition.token == *True)
            return Evaluate::evaluate(args[i + 1]);
    }
    if (args.size() % 2) {
        return Evaluate::evaluate(args[args.size() - 1]);
    }
    return new SyntaxTreeNode();
}
