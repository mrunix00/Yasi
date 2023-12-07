#include "multiply.h"
#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include <sstream>
#include <string>

SyntaxTreeNode Multiply::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int int_result = 1;
    float dec_result = 1;

    for (const auto &arg: args) {
        auto evArg = Evaluate::evaluate(arg).token;
        if (evArg.type == Token::Integer) {
            int_result *= std::stoi(evArg.token);
        } else if (evArg.type == Token::Decimal) {
            dec_result *= std::stof(evArg.token);
        } else {
            throw SyntaxError(arg.token.token + " is not a number",
                              arg.token.line, arg.token.column);
        }
    }

    if (dec_result != 1) {
        std::stringstream s;
        s << (float) int_result * dec_result;
        return SyntaxTreeNode(Token(Token::Decimal, s.str()));
    } else {
        return SyntaxTreeNode(Token(Token::Integer, std::to_string(int_result)));
    }
}
