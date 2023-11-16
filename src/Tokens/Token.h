#ifndef DUMMYLISP_TOKEN_H
#define DUMMYLISP_TOKEN_H

#include <iostream>

class Token {
public:
    std::string symbol;

    bool operator==(Token &token) const {
        return symbol == ((Token) token).symbol;
    }
};

#endif
