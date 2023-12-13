#ifndef YASI_LEXER_H
#define YASI_LEXER_H

#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Token {
protected:
    int integer;
    float decimal;

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

    Token(TokenType type, const std::string &token)
        : type(type), token(token) {
        if (type == Token::Integer) {
            integer = std::stoi(token);
        } else if (type == Token::Decimal) {
            decimal = std::stof(token);
        }
    }

    Token(TokenType type, const std::string &token,
          int line, int column)
        : type(type), token(token),
          line(line), column(column) {
        if (type == Token::Integer) {
            integer = std::stoi(token);
        } else if (type == Token::Decimal) {
            decimal = std::stof(token);
        }
    }

    Token(int token)
        : type(Token::Integer), integer(token) {}

    Token(float token)
        : type(Token::Decimal), decimal(token) {}


    int asInteger() {
        if (type == Token::Decimal)
            integer = (int) integer;
        return integer;
    }
    float asDecimal() {
        if (type == Token::Integer)
            decimal = (float) integer;
        return decimal;
    }

    std::string asString() {
        if (token.empty() && type != Token::String) {
            if (type == Token::Integer) {
                token = std::to_string(integer);
            } else if (type == Token::Decimal) {
                std::stringstream s;
                s << decimal;
                token = s.str();
            }
        }
        return token;
    }

    bool operator==(const Token &object) const {
        if (type == object.type) {
            if (type == Integer) {
                return object.integer == integer;
            } else if (type == Decimal) {
                return std::to_string(object.decimal) == std::to_string(decimal);
            } else {
                return object.token == token;
            }
        }
        return false;
    }
};

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string &line);
};

#endif
