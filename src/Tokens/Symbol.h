#ifndef DUMMYLISP_SYMBOL_H
#define DUMMYLISP_SYMBOL_H

#include "Token.h"

class Symbol : public Token {
public:
    explicit Symbol(std::string sym) {
        symbol = std::move(sym);
    }
};

#endif //DUMMYLISP_SYMBOL_H
