#include "Token.h"
#include <limits>
#include <sstream>

Token::Token(
        const TokenType type,
        const std::string &token,
        const int line, const int column)
    : type(type),
      token(token),
      line(line), column(column) {
    if (type == Token::Integer) {
        integer = std::stoi(token);
    } else if (type == Token::Decimal) {
        decimal = std::stof(token);
    }
}

Token::Token(
        const TokenType type,
        const std::string &token)
    : type(type),
      token(token) {
    if (type == Integer) {
        integer = std::stoi(token);
    } else if (type == Decimal) {
        decimal = std::stof(token);
    }
}

std::string Token::asString() const {
    if (type != String) {
        if (type == Integer) {
            return std::to_string(integer);
        } else if (type == Decimal) {
            std::stringstream s;
            s << decimal;
            return s.str();
        }
    }
    return token;
}

int Token::asInteger() const {
    if (type == Decimal)
        return static_cast<int>(decimal);
    return integer;
}

float Token::asDecimal() const {
    if (type == Integer)
        return static_cast<float>(integer);
    return decimal;
}

bool Token::operator==(const Token &object) const {
    switch (type) {
        case Invalid:
            return true;
        case Integer:
            return object.asInteger() == asInteger();
        case Decimal:
            return (object.asDecimal() - asDecimal()) < std::numeric_limits<double>::epsilon();
        case Boolean:
            return object.token[1] == token[1];
        default:
            return object.token == token;
    }
}

