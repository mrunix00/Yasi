#include "add.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"

#include <string>

SyntaxTreeNode Add::evaluate(const std::vector<SyntaxTreeNode> &args) {
    float result = 0;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::Integer || evArg.type == Token::Decimal) {
            result += evArg.asDecimal();
        } else {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
        }
    }

    if ((int) result == result) {
        return Token((int) result);
    } else {
        return Token(result);
    }
}
