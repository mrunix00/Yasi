#ifndef DUMMYLISP_INTEGER_H
#define DUMMYLISP_INTEGER_H

#include "Token.h"

class Integer : public Token {
public:
    explicit Integer(int integer) {
        symbol = std::to_string(integer);
    }
};

#endif //DUMMYLISP_INTEGER_H
