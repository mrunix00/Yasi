#include "Print.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/RecursiveEvaluation.h"
#include <string>

namespace RecursiveEvaluation {
    SyntaxTreeNode *Print::evaluate(const std::vector<SyntaxTreeNode *> &args) {
        auto *result = new std::string;
        for (const auto &arg: args) {
            auto evArg = *RecursiveEvaluation::evaluate(arg)->token;
            if (evArg.type == Token::String) {
                *result += evArg.token->substr(1, evArg.token->size() - 2);
            } else {
                *result += *evArg.asString();
            }
        }
        return new SyntaxTreeNode(new Token(Token::String, result));
    }
}