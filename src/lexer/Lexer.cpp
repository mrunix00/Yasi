#include "Lexer.h"
#include <regex>

std::vector<Token *> tokenize(const std::string &line) {
    std::vector<Token *> result;
    std::string currentToken;
    int currentLine = 1;
    int currentLineChar = 0;
    int currentColumn = 0;
    bool is_a_comment = false;

    for (const auto c: line + "\n") {
        currentLineChar++;

        if (c == ';')
            is_a_comment = true;

        if (is_a_comment && c != '\n')
            continue;

        if (c == '\n')
            is_a_comment = false;

        if (((c == '(' || c == ')') && currentToken[0] == '"') ||
            (c != '(' && c != ')' && (c != ' ' || currentToken[0] == '"') &&
             (c != '"' || currentToken[0] != '"') && c != '\n')) {
            currentToken.append(1, c);
            continue;
        }
        currentColumn++;

        if (!currentToken.empty()) {
            if (std::regex_match(
                        currentToken,
                        std::regex(R"(^[+-]?((\d+(\.\d+)?)|(\.\d+))$)"))) {
                result.emplace_back(new Token(Token::Number, currentToken,
                                              currentLine, currentColumn));
            } else if (c != '"') {
                result.emplace_back(new Token(Token::Symbol, currentToken,
                                              currentLine, currentColumn));
            } else {
                currentToken.append(1, '"');
                result.emplace_back(new Token(Token::String, currentToken,
                                              currentLine, currentColumn));
            }

            if (c == '\n') {
                currentLine++;
                currentLineChar = 0;
            }
            currentColumn = currentLineChar;
        }

        currentToken.clear();
        if (c == '(')
            result.emplace_back(new Token(Token::OpenBracket, "(",
                                          currentLine, currentColumn));
        else if (c == ')')
            result.emplace_back(new Token(Token::ClosedBracket, ")",
                                          currentLine, currentColumn));
    }

    return result;
}
