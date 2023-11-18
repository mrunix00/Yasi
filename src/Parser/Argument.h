#ifndef DUMMYLISP_ARGUMENT_H
#define DUMMYLISP_ARGUMENT_H

#include "../Tokens/Token.h"
#include <vector>

class Argument {
    Token token;
    std::vector<Argument> arguments;

public:
    explicit Argument(Token token) : token(std::move(token)) {}

    explicit Argument(
            Token token,
            const std::vector<Argument> &arguments
    ) : token(std::move(token)), arguments(arguments) {}

    bool operator==(const Argument &argument) const {
        return argument.token == token;
    }

    Argument() = default;
};

#endif
