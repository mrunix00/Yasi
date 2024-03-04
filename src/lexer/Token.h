#pragma once

#include <string>

class Token {
protected:
    double number{};

public:
    enum TokenType {
        OpenBracket,
        ClosedBracket,
        Symbol,
        Number,
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

    explicit Token(const double token)
        : number(token), type(Number) {}

    [[nodiscard]] double asNumber() const;
    [[nodiscard]] std::string asString() const;

    bool operator==(const Token &object) const;
};
