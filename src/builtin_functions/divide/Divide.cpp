#include "Divide.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include <string>

SyntaxTreeNode Divide::evaluate(const std::vector<SyntaxTreeNode> &args) {
    if (args.empty()) {
        throw SyntaxError("At least 1 argument was expected but none were found");
    }
    int result = std::stoi(Evaluate::evaluate(args[0]).token.token);

    for (int i = 1; i < args.size(); i++) {
        auto arg = Evaluate::evaluate(args[i]).token;
        if (arg.type != Token::Integer) {
            throw SyntaxError(args[i].token.token + " is not a number",
                              args[i].token.line, args[i].token.column);
        }

        auto operand = std::stoi(arg.token);
        if (operand == 0) {
            throw SyntaxError("Division by zero", arg.line, arg.column);
        }
        result /= operand;
    }

    return SyntaxTreeNode(Token(Token::Integer, std::to_string(result)));
}
