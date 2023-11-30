#include "subtract.h"
#include "eval/eval.h"

SyntaxTreeNode Subtract::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = std::stoi(Evaluate::evaluate(args[0]).token.token);

    for (int i = 1; i < args.size(); i++) {
        auto arg = Evaluate::evaluate(args[i]).token;
        result -= std::stoi(arg.token);
    }

    return SyntaxTreeNode(Token(Token::Integer, std::to_string(result)));
}
