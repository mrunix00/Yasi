#include "eval/eval.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "read.hpp"
#include "utils/StdOut.h"
#include "utils/printAST.h"
#include "utils/printTokens.h"
#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Yasi v0.0.0\n";

    bool displayTokens = false;
    bool displayAST = false;
    StdOut *stdOut;

    int opt;
    while ((opt = getopt(argc, argv, "at")) != -1) {
        switch (opt) {
            case 't':
                displayTokens = true;
                break;
            case 'a':
                displayAST = true;
                break;
        }
    }

    if (displayTokens || displayAST) {
        stdOut = new StdOut;
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

            auto ast = Parser::parse(tokens);
            if (displayAST) {
                print_ast(stdOut, ast);
            }

            auto result = Evaluate::evaluate(ast);
            if (result.token.type != Token::Invalid)
                std::cout << result.token.token << '\n';
        } catch (SyntaxError &error) {
            std::cout << "SyntaxError (" << error.line
                      << ':' << error.column << "): "
                      << error.message << '\n';
        }
    }
}
