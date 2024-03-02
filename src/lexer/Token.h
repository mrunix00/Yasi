#pragma once

#include <string>

class Token {
protected:
    int integer{};
    double decimal{};

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

    Token() : type(Invalid) {}

    Token(TokenType type, const std::string &token);

    Token(TokenType type, const std::string &token,
          int line, int column);

    explicit Token(const int token)
        : integer(token), type(Integer) {}

    explicit Token(const double token)
        : decimal(token), type(Decimal) {}

    [[nodiscard]] int asInteger() const;
    [[nodiscard]] double asDecimal() const;
    [[nodiscard]] std::string asString() const;

    bool operator==(const Token &object) const;
};
