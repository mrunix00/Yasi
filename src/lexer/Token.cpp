#include "Token.h"
#include <limits>
#include <sstream>

Token::Token(
        Token::TokenType type,
        std::string *token,
        int line, int column)
    : type(type),
      token(token),
      line(line), column(column) {
    if (type == Token::Integer) {
        integer = std::stoi(*token);
    } else if (type == Token::Decimal) {
        decimal = std::stof(*token);
    }
}

Token::Token(
        Token::TokenType type,
        std::string *token)
    : type(type),
      token(token) {
    if (type == Token::Integer) {
        integer = std::stoi(*token);
    } else if (type == Token::Decimal) {
        decimal = std::stof(*token);
    }
}

std::string *Token::asString() {
    if (token == nullptr && type != Token::String) {
        if (type == Token::Integer) {
            token = new std::string(std::to_string(integer));
        } else if (type == Token::Decimal) {
            std::stringstream s;
            s << decimal;
            token = new std::string(s.str());
        }
    }
    return token;
}

int Token::asInteger() const {
    if (type == Token::Decimal)
        return (int) decimal;
    return integer;
}

float Token::asDecimal() const {
    if (type == Token::Integer)
        return (float) integer;
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
            return (*object.token)[1] == (*token)[1];
        default:
            return *object.token == *token;
    }
}
Token::Token(
        Token::TokenType type,
        const std::string &token)
    : type(type),
      token(new std::string(token)) {
    if (type == Token::Integer) {
        integer = std::stoi(token);
    } else if (type == Token::Decimal) {
        decimal = std::stof(token);
    }
}
Token::Token(
        TokenType type,
        const std::string &token,
        int line,
        int column)
    : type(type),
      token(new std::string(token)),
      line(line), column(column) {
    if (type == Token::Integer) {
        integer = std::stoi(token);
    } else if (type == Token::Decimal) {
        decimal = std::stof(token);
    }
}