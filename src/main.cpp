#include <cstdlib>
#include <iostream>
#include "read.hpp"
#include "lexer/Lexer.h"
#include "eval/eval.h"
#include "parser/Parser.h"
#include "exceptions/SyntaxError.h"

int main() {
    std::cout << "dummyLisp 0.0.0 Interpreter\n";

    std::string userInput;
    while (true) {
        try {
            userInput = readCommand();
        } catch (ProgramExit &exception) {
            return EXIT_SUCCESS;
        }

        try {
            auto result = Evaluate::evaluate(
                    Parser::parse(Lexer::tokenize(userInput))
            );
            std::cout << result.token.token << '\n';
        } catch (SyntaxError &error) {
            std::cout << error.message << '\n';
        }

    }
}
