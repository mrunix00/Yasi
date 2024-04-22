#pragma once

#include <string>

class Token {
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

    Token(TokenType type, std::string token);

    Token(TokenType type, std::string token,
          int line, int column);

    [[nodiscard]] double asNumber() const;

    bool operator==(const Token &object) const;

    bool operator!=(const Token &object) const;
};
