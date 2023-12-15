#include "Print.h"
#include "evaluation/Evaluate.h"
#include "parser/SyntaxTreeNode.h"
#include <string>

SyntaxTreeNode* Print::evaluate(const std::vector<SyntaxTreeNode*> &args) {
    std::string result;
    for (const auto &arg: args) {
        auto evArg = *Evaluate::evaluate(arg)->token;
        if (evArg.type == Token::String) {
            result += evArg.token.substr(1, evArg.token.size() - 2);
        } else {
            result += evArg.asString();
        }
    }
    return new SyntaxTreeNode(new Token(Token::String, result));
}
