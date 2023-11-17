#ifndef DUMMYLISP_LEXER_H
#define DUMMYLISP_LEXER_H

#include "../Tokens/Token.h"
#include <vector>

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};


#endif
