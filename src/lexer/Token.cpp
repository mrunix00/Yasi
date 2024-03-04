#include "Token.h"
#include <limits>
#include <sstream>
#include <utility>

Token::Token(
        const TokenType type,
        const std::string &token,
        const int line, const int column)
    : type(type),
      token(token),
      line(line), column(column) {
    if (type == Token::Number) {
        number = std::stof(token);
    }
}

Token::Token(
        const TokenType type,
        const std::string &token)
    : type(type),
      token(token) {
    if (type == Token::Number) {
        number = std::stof(token);
    }
}

std::string Token::asString() const {
    if (type != String) {
        if (type == Number) {
            std::stringstream s;
            s << number;
            return s.str();
        }
    }
    return token;
}

double Token::asNumber() const {
    return number;
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

