#include <cstdlib>
#include <iostream>
#include "read.hpp"
#include "Lexer/Lexer.h"


int main() {
    std::cout << "dummyLisp 0.0.0 Interpreter\n";

    std::string userInput;
    while (true) {
        try {
            userInput = readCommand();
        } catch (ProgramExit &exception) {
            return EXIT_SUCCESS;
        }

        if (!userInput.empty()) {
            auto tokens = Lexer::tokenize(userInput);
            std::cout << '[';
            for (const auto &token: tokens) {
                std::cout << " '" << token.token << "', ";
            }
            std::cout << "\b\b ]\n";
        }
    }
}
