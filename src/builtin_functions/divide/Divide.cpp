#include "Divide.h"

SyntaxTreeNode Divide::evaluate(const std::vector<SyntaxTreeNode> &args) {
    int result = std::stoi(args[0].token.token);

    for (int i = 1; i < args.size(); i++) {
        result /= std::stoi(args[i].token.token);
    }

    return SyntaxTreeNode(
            Token(
                    Token::Integer,
                    std::to_string(result)
            )
    );
}
