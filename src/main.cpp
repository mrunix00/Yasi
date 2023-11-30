#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "read.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Yasi v0.0.0\n";

    std::string userInput;
    while (true) {
        try {
            userInput = readCommand();
        } catch (ProgramExit &exception) {
            return EXIT_SUCCESS;
        }

        try {
            auto result =
                    Evaluate::evaluate(Parser::parse(Lexer::tokenize(userInput)));
            std::cout << result.token.token << '\n';
        } catch (SyntaxError &error) {
            std::cout << error.message << '\n';
        }
    }
}
