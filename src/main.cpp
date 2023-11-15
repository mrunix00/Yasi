#include "read.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    std::cout << "dummyLisp 0.0.0 Interpreter\n";

    std::string userInput;
    while (true) {
        try {
            userInput = readCommand();
        } catch (ProgramExit &exception) {
            return EXIT_SUCCESS;
        }
        std::cout << userInput << '\n';
    }
}
