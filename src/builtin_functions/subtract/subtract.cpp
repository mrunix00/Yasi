#include "subtract.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

SyntaxTreeNode Subtract::evaluate(const std::vector<SyntaxTreeNode> &args) {
    if (args.empty()) {
        throw SyntaxError("At least 1 argument was expected but none were found");
    }

    float result;

    auto firstArg = Evaluate::evaluate(args[0]).token;
    result = std::stof(firstArg.token);

    for (int i = 1; i < args.size(); i++) {
        auto arg = Evaluate::evaluate(args[i]).token;
        if (arg.type == Token::Integer || arg.type == Token::Decimal) {
            result -= std::stof(arg.token);
        } else {
            throw SyntaxError(args[i].token.token + " is not a number",
                              args[i].token.line, args[i].token.column);
        }
    }

    if ((int) result == result) {
        return Token(Token::Integer, std::to_string((int) result));
    } else {
        std::stringstream s;
        s << result;
        return Token(Token::Decimal, s.str());
    }
}
