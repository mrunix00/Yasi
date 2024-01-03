#include "bytecode/compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "read.hpp"
#include "recursive_evaluation/RecursiveEvaluation.h"
#include "utils/StdOut.h"
#include "utils/break_lines.h"
#include "utils/printAST.h"
#include "utils/printTokens.h"
#include <fstream>
#include <getopt.h>
#include <iostream>

struct options {
    bool displayTokens = false;
    bool displayAST = false;
    bool dumpBytecode = false;
};

void exec_program(const std::string &program, struct options opts) {
    static auto *stdOut = new StdOut;
    auto expressions = break_lines(program);

    for (const auto &expression: expressions) {
        auto tokens = Lexer::tokenize(expression);
        try {
            if (opts.displayTokens) {
                printTokens(stdOut, tokens);
            }

            auto ast = Parser::parse(tokens);
            if (opts.displayAST && ast != nullptr) {
                print_ast(stdOut, *ast);
            }

            if (opts.dumpBytecode && ast != nullptr) {
                std::vector<Bytecode::Instruction *> instructions;
                static Bytecode::Compiler compiler;
                compiler.compile(*ast, instructions);
                for (auto instruction: instructions) {
                    std::cout << instruction->toString() << '\n';
                }
            } else {
                auto result = RecursiveEvaluation::evaluate(ast);
                if (result != nullptr && (*result).token->type != Token::Invalid)
                    std::cout << *result->token->asString() << '\n';
            }
        } catch (SyntaxError &error) {
            std::cout << "SyntaxError (" << error.line
                      << ':' << error.column << "): "
                      << error.message << '\n';
        }
    }
}

int main(int argc, char *argv[]) {
    struct options opts;

    int opt;
    while ((opt = getopt(argc, argv, "atd")) != -1) {
        switch (opt) {
            case 't':
                opts.displayTokens = true;
                break;
            case 'a':
                opts.displayAST = true;
                break;
            case 'd':
                opts.dumpBytecode = true;
                break;
            default:
                break;
        }
    }
    argc -= optind;
    argv += optind;

    std::string userInput;

    if (argc > 1) {
        std::ifstream file_stream(argv[1]);
        std::string line;
        while (std::getline(file_stream, line))
            userInput += line;
        exec_program(userInput, opts);
    } else {
        std::cout << "Yasi v0.0.0\n";
        while (true) {
            try {
                userInput = readCommand();
            } catch (ProgramExit &exception) {
                return EXIT_SUCCESS;
            }

            exec_program(userInput, opts);
        }
    }
}
