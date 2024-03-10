#include "printTokens.h"
#include <iostream>

void printTokens(const std::vector<Token*> &tokens) {
    std::string output = "[";
    for (const auto &token: tokens) {
        switch (token->type) {
            case Token::String:
            case Token::Number:
                output += token->token + ", ";
                break;
            default:
                output += "'" + token->token + "', ";
        }
    }
    output.erase(output.size() - 2, 2);
    output = output + ']';
    
    std::cout << output << '\n';
}
