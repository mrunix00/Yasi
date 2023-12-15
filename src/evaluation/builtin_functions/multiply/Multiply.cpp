#include "Multiply.h"
#include "evaluation/Evaluate.h"
#include "exceptions/SyntaxError.h"
#include <string>

SyntaxTreeNode *Multiply::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    float result = 1;
    for (const auto &arg: args) {
        auto evArg = *Evaluate::evaluate(arg)->token;
        if (evArg.type == Token::Integer || evArg.type == Token::Decimal) {
            result *= evArg.asDecimal();
        } else {
            throw SyntaxError(*arg->token->token + " is not a number",
                              (*arg->token).line, (*arg->token).column);
        }
    }

    if ((int) result == result) {
        return new SyntaxTreeNode(new Token((int) result));
    } else {
        return new SyntaxTreeNode(new Token(result));
    }
}
