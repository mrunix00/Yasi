#include <cstring>
#include "Lexer.h"

std::vector<Token> Lexer::parse(const std::string &line) {
    std::vector<Token> result;
    std::string currentToken;

    for (auto c: line) {
        if (c == '(' || c == ')' || c == ' ') {
            if (!currentToken.empty()) {
                if (strspn(currentToken.c_str(), "0123456789")) {
                    result.push_back(Integer(std::stoi(currentToken)));
                } else {
                    result.push_back(Symbol(currentToken));
                }
            }

            currentToken = "";
            if (c == '(') result.push_back(OpenBracket());
            else if (c == ')') result.push_back(ClosedBracket());
        } else {
            currentToken.append(1, c);
        }
    }

    return result;
}
