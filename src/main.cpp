#include <cstdlib>
#include <iostream>
#include "read.hpp"


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
