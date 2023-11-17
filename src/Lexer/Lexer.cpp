#include <cstring>
#include "Lexer.h"

std::vector<Token> Lexer::tokenizer(const std::string &line) {
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
                result.push_back(Integer(std::stoi(currentToken)));
            } else {
                result.push_back(Symbol(currentToken));
            }
        }

        currentToken = "";
        if (c == '(') result.push_back(OpenBracket());
        else if (c == ')') result.push_back(ClosedBracket());
    }

    return result;
}
