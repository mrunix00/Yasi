#include "Cond.h"
#include "recursive_evaluation/RecursiveEvaluation.h"

static Token *True = new Token(Token::Boolean, new std::string("#t"));

SyntaxTreeNode *RecursiveEvaluation::Cond::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    for (int i = 0; i < args.size(); i += 2) {
        auto condition = *RecursiveEvaluation::evaluate(args[i]);
        if (*condition.token == *True)
            return RecursiveEvaluation::evaluate(args[i + 1]);
    }
    if (args.size() % 2) {
        return RecursiveEvaluation::evaluate(args[args.size() - 1]);
    }
    return new SyntaxTreeNode();
}
