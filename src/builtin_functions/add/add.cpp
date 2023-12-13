#include "add.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include <cmath>
#include <sstream>
#include <string>

SyntaxTreeNode Add::evaluate(const std::vector<SyntaxTreeNode> &args) {
    float result = 0;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::Integer || evArg.type == Token::Decimal) {
            result += std::stof(evArg.token);
        } else {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
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
