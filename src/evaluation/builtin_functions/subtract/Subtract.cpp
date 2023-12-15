#include "Subtract.h"
#include "evaluation/Evaluate.h"
#include "exceptions/SyntaxError.h"
#include <string>

SyntaxTreeNode *Subtract::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    if (args.empty()) {
        throw SyntaxError("At least 1 argument was expected but none were found");
    }

    float result;

    auto firstArg = *Evaluate::evaluate(args[0])->token;
    result = firstArg.asDecimal();

    for (int i = 1; i < args.size(); i++) {
        auto arg = *Evaluate::evaluate(args[i])->token;
        if (arg.type == Token::Integer || arg.type == Token::Decimal) {
            result -= arg.asDecimal();
        } else {
            throw SyntaxError((*args[i]->token).token + " is not a number",
                              (*args[i]->token).line, (*args[i]->token).column);
        }
    }

    if ((int) result == result) {
        return new SyntaxTreeNode(new Token((int) result));
    } else {
        return new SyntaxTreeNode(new Token(result));
    }
}
