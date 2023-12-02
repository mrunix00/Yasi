#include "add.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"

SyntaxTreeNode Add::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = 0;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type != Token::Integer) {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
        }
        result += std::stoi(evArg.token);
    }

    return SyntaxTreeNode(Token(Token::Integer, std::to_string(result)));
}
