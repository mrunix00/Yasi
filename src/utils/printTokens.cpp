#include "printTokens.h"

void printTokens(OutputSource *outputSource,
                 const std::vector<Token*> &tokens) {
    std::string output = "[";
    for (const auto &token: tokens) {
        switch (token->type) {
            case Token::String:
            case Token::Integer:
                output += *token->token + ", ";
                break;
            default:
                output += "'" + *token->token + "', ";
        }
    }
    output.erase(output.size() - 2, 2);
    output = output + ']';
    
    outputSource->out(output);
}
