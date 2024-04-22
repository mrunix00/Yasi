#include "Token.h"
#include <limits>
#include <utility>

Token::Token(
        const TokenType type,
        std::string token,
        const int line, const int column)
    : type(type),
      token(std::move(token)),
      line(line), column(column) {}

Token::Token(
        const TokenType type,
        std::string token)
    : type(type),
      token(std::move(token)) {}

double Token::asNumber() const {
    return std::stod(token);
}

bool Token::operator==(const Token &object) const {
    switch (type) {
        case Invalid:
            return true;
        case Number:
            return (object.asNumber() - asNumber()) < std::numeric_limits<double>::epsilon();
        case Boolean:
            return object.token[1] == token[1];
        default:
            return object.token == token;
    }
}

bool Token::operator!=(const Token &object) const {
    return !operator==(object);
}
