#ifndef DUMMYLISP_LEXER_H
#define DUMMYLISP_LEXER_H

#include "../tokens/Token.h"
#include <vector>

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};


#endif
