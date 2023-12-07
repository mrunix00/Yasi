#include "multiply.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include <sstream>
#include <string>

SyntaxTreeNode Multiply::evaluate(const std::vector<SyntaxTreeNode> &args) {
    float result = 1;
    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::Integer || evArg.type == Token::Decimal) {
            result *= std::stof(evArg.token);
        } else {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
        }
    }

    std::stringstream s;
    s << result;
    if (int(result) != result) return Token(Token::Decimal, s.str());
    return Token(Token::Integer, s.str());
}
