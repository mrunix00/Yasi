#ifndef YASI_LEXER_H
#define YASI_LEXER_H

#include <string>
#include <utility>
#include <vector>

class Token {
public:
    enum TokenType {
        OpenBracket,
        ClosedBracket,
        Symbol,
        Integer,
        Decimal,
        String,
        Invalid
    };

    TokenType type;
    std::string token;
    int line = 0;
    int column = 0;

    Token() : type(Token::Invalid) {}

    Token(TokenType type, std::string token)
        : type(type), token(std::move(token)) {}

    Token(TokenType type, std::string token,
          int line, int column)
        : type(type), token(std::move(token)),
          line(line), column(column) {}

    bool operator==(const Token &object) const {
        return token == object.token && type == object.type;
    }
};

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};

#endif
