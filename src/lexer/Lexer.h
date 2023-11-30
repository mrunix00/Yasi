#ifndef YASI_LEXER_H
#define YASI_LEXER_H

#include <iostream>
#include <utility>
#include <vector>

class Token {
public:
    enum TokenType {
        OpenBracket,
        ClosedBracket,
        Symbol,
        Integer,
        String,
        Invalid
    };

    TokenType type;
    std::string token;

    Token() : type(Token::Invalid) {}

    Token(TokenType type, std::string token)
        : type(type), token(std::move(token)) {}

    bool operator==(const Token &object) const { return token == object.token; }
};

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};

#endif
