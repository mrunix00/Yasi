#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "read.hpp"
#include "utils/printTokens.h"
#include "utils/StdOut.h"
#include <bits/getopt_core.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Yasi v0.0.0\n";

    bool displayTokens = false;
    StdOut *stdOut;

    int opt;
    while ((opt = getopt(argc, argv, "t")) != -1) {
        switch (opt) {
            case 't':
                displayTokens = true;
                stdOut = new StdOut;
                break;
        }
    }

    std::string userInput;
    while (true) {
        try {
            userInput = readCommand();
        } catch (ProgramExit &exception) {
            return EXIT_SUCCESS;
        }

        auto tokens = Lexer::tokenize(userInput);

        try {
            if (displayTokens) {
                printTokens(stdOut, tokens);
            }
            auto result = Evaluate::evaluate(Parser::parse(tokens));
            std::cout << result.token.token << '\n';
        } catch (SyntaxError &error) {
            std::cout << "SyntaxError (" << error.line
                      << ':' << error.column << "): "
                      << error.message << '\n';
        }
    }
}
