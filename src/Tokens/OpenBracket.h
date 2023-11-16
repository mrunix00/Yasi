#ifndef DUMMYLISP_OPENBRACKET_H
#define DUMMYLISP_OPENBRACKET_H

#include "Token.h"

class OpenBracket : public Token {
public:
    OpenBracket() { symbol = "("; };
};

#endif