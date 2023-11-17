#include <cstring>
#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string &line) {
    std::vector<Token> result;
    std::string currentToken;

    for (auto c: line) {
        if (c != '(' && c != ')'
            && (c != ' ' || currentToken[0] == '"')
            && (c != '"' || currentToken[0] != '"')
                ) {
            currentToken.append(1, c);
            continue;
        }

        if (!currentToken.empty()) {
            if (strspn(currentToken.c_str(), "0123456789")) {
                result.emplace_back(Token::Integer, currentToken);
            } else if (c != '"') {
                result.emplace_back(Token::Symbol, currentToken);
            } else {
                currentToken.append(1, '"');
                result.emplace_back(Token::String, currentToken);
            }
        }

        currentToken = "";
        if (c == '(')
            result.emplace_back(Token::OpenBracket, "(");
        else if (c == ')')
            result.emplace_back(Token::ClosedBracket, ")");
    }

    return result;
}
