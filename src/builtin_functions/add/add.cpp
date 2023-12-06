#include "add.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include <sstream>
#include <string>

SyntaxTreeNode Add::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int int_res = 0;
    float dec = 0;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::Integer) {
            int_res += std::stoi(evArg.token);
        } else if (evArg.type == Token::Decimal) {
            dec += std::stof(evArg.token);
        } else {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
        }
    }

    if (dec == 0) {
        return SyntaxTreeNode(Token(Token::Integer, std::to_string(int_res)));
    } else {
        std::stringstream s;
        s << (float) int_res + dec;
        return SyntaxTreeNode(Token(Token::Decimal, s.str()));
    }
}
