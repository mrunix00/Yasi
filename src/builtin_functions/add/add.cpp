#include "add.h"

SyntaxTreeNode Add::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = 0;

    for (const auto &arg: args) {
        result += std::stoi(arg.token.token);
    }

    return SyntaxTreeNode(
            Token(
                    Token::Integer,
                    std::to_string(result)
            )
    );
}
