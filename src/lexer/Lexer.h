#ifndef YASI_LEXER_H
#define YASI_LEXER_H

#include "Token.h"
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};

#endif
