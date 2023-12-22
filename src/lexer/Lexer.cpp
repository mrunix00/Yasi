#include "Lexer.h"
#include <regex>

std::vector<Token *> Lexer::tokenize(const std::string &line) {
    std::vector<Token *> result;
    std::string currentToken;
    int currentLine = 1;
    int currentLineChar = 0;
    int currentColumn = 0;

    for (auto c: line + "\n") {
        currentLineChar++;

        if (((c == '(' || c == ')') && currentToken[0] == '"') ||
            (c != '(' && c != ')' && (c != ' ' || currentToken[0] == '"') &&
                    (c != '"' || currentToken[0] != '"') && c != '\n')) {
            currentToken.append(1, c);
            continue;
        }
        currentColumn++;

        if (!currentToken.empty()) {
            if (std::regex_match(currentToken, std::regex("[+-]?[0-9]+"))) {
                result.emplace_back(new Token(Token::Integer, new std::string(currentToken),
                                              currentLine, currentColumn));
            } else if (std::regex_match(currentToken,
                                        std::regex("-?[0-9]+([\\.][0-9]+)?"))) {
                result.emplace_back(new Token(Token::Decimal, new std::string(currentToken),
                                              currentLine, currentColumn));
            } else if (c != '"') {
                result.emplace_back(new Token(Token::Symbol, new std::string(currentToken),
                                              currentLine, currentColumn));
            } else {
                currentToken.append(1, '"');
                result.emplace_back(new Token(Token::String, new std::string(currentToken),
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
            result.emplace_back(new Token(Token::OpenBracket, new std::string("("),
                                          currentLine, currentColumn));
        else if (c == ')')
            result.emplace_back(new Token(Token::ClosedBracket, new std::string(")"),
                                          currentLine, currentColumn));
    }

    return result;
}
