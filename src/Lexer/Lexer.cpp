#include <cstring>
#include "Lexer.h"

std::vector<Token> Lexer::tokenize(const std::string &line) {
    std::vector<Token> result;
    std::string currentToken;

    const std::string separators = "() ";
    for (auto c: line) {
        if (separators.find(c) == std::string::npos) {
            currentToken.append(1, c);
            continue;
        }

        if (!currentToken.empty()) {
            if (strspn(currentToken.c_str(), "0123456789")) {
                result.emplace_back(Token::Integer, currentToken);
            } else {
                result.emplace_back(Token::Symbol, currentToken);
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
