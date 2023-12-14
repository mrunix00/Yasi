#ifndef YASI_TOKEN_H
#define YASI_TOKEN_H

#include <string>

class Token {
protected:
    int integer{};
    float decimal{};

public:
    enum TokenType {
        OpenBracket,
        ClosedBracket,
        Symbol,
        Integer,
        Decimal,
        String,
        Boolean,
        Invalid
    };

    TokenType type;
    std::string token;
    int line = 0;
    int column = 0;

    Token() : type(Token::Invalid) {}

    Token(TokenType type, const std::string &token);

    Token(TokenType type, const std::string &token,
          int line, int column);

    explicit Token(int token)
        : type(Token::Integer), integer(token) {}

    explicit Token(float token)
        : type(Token::Decimal), decimal(token) {}

    int asInteger() const;
    float asDecimal() const;
    std::string asString();

    bool operator==(const Token &object) const;
};

#endif
