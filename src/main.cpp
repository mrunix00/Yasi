#include "bytecode/compiler/Compiler.h"
#include "bytecode/vm/Interpreter.h"
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
    bool executeBytecode = false;
    bool compilerOptimization = false;
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

            if ((opts.dumpBytecode || opts.executeBytecode) && ast != nullptr) {
                static auto compiler = Bytecode::Compiler(opts.compilerOptimization);
                compiler.compile(*ast);
                for (size_t i = 0; i < compiler.program.segments.size() && opts.dumpBytecode; i++) {
                    std::cout << ':' << i << '\n';
                    for (size_t j = 0; j < compiler.program.segments[i]->instructions.size(); j++)
                        std::cout << j << '\t' << compiler.program.segments[i]->instructions[j]->toString() << '\n';
                    std::cout << '\n';
                }

                if (opts.executeBytecode) {
                    static auto interpreter = Bytecode::Interpreter();
                    interpreter.execute(compiler.program);
                    std::cout << interpreter.vm.stackTop()->literal->int_literal << '\n';
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
    while ((opt = getopt(argc, argv, "atbdO")) != -1) {
        switch (opt) {
            case 't':
                opts.displayTokens = true;
                break;
            case 'a':
                opts.displayAST = true;
                break;
            case 'b':
                opts.executeBytecode = true;
                break;
            case 'd':
                opts.dumpBytecode = true;
                break;
            case 'O':
                opts.compilerOptimization = true;
                break;
            default:
                break;
        }
    }
    argc -= optind;
    argv += optind;

    std::string userInput;

    if (argc > 0) {
        std::ifstream file_stream(argv[0]);
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
