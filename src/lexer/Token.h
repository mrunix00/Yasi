#pragma once

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
    std::string *token{};
    int line = 0;
    int column = 0;

    Token() : type(Invalid) {}

    Token(TokenType type, std::string *token);
    Token(TokenType type, const std::string &token);

    Token(TokenType type, std::string *token,
          int line, int column);

    explicit Token(const int token)
        : integer(token), type(Integer) {}

    explicit Token(const float token)
        : decimal(token), type(Decimal) {}

    [[nodiscard]] int asInteger() const;
    [[nodiscard]] float asDecimal() const;
    std::string *asString();

    bool operator==(const Token &object) const;
    Token(TokenType type, const std::string &token, int line, int column);
};
