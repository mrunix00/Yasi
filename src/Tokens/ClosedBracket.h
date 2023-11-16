#ifndef DUMMYLISP_CLOSEDBRACKET_H
#define DUMMYLISP_CLOSEDBRACKET_H

#include "Token.h"

class ClosedBracket : public Token {
public:
    ClosedBracket() {
        symbol = ")";
    };
};

#endif