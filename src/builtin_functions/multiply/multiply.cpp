#include "multiply.h"
#include "eval/eval.h"

SyntaxTreeNode Multiply::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = 1;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        result *= std::stoi(evArg.token);
    }

    return SyntaxTreeNode(Token(Token::Integer, std::to_string(result)));
}
