#include "multiply.h"

SyntaxTreeNode Multiply::evaluate() {
    int result = 1;

    for (const auto &arg: args) {
        result *= std::stoi(arg.token.token);
    }

    return SyntaxTreeNode(
            Token(
                    Token::Integer,
                    std::to_string(result)
            )
    );
}
