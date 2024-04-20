#include "bytecode/compiler/Optimizer.h"
#include "bytecode/instructions/Return.h"
#include "bytecode/vm/Interpreter.h"
#include "exceptions/SyntaxError.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "read.hpp"
#include "utils/break_lines.h"
#include "utils/printTokens.h"
#include <fstream>
#include <getopt.h>
#include <iostream>

struct options {
    bool displayTokens = false;
    bool dumpBytecode = false;
};

void exec_program(const std::string &program, struct options opts) {
    const auto expressions = break_lines(program);
    static auto compiled_bytecode = Bytecode::Program();
    static auto interpreter = Bytecode::Interpreter();

    try {
        for (const auto &expression: expressions) {
            auto tokens = tokenize(expression);
            if (opts.displayTokens) {
                printTokens(tokens);
            }

            const auto ast = parse(tokens);

            ast->compile(compiled_bytecode);
            delete ast;

        }

        for (size_t i = 1; i < compiled_bytecode.segments.size(); i++) {
            const auto segment = compiled_bytecode.segments[i];
            if (Bytecode::Optimizer::is_tail_recursive(*segment, i))
                Bytecode::Optimizer::optimize_tail_calls(*segment);
        }


        if (opts.dumpBytecode) {
            for (size_t i = 0; i < compiled_bytecode.segments.size(); i++) {
                std::cout << ':' << i << '\n';
                for (size_t j = 0; j < compiled_bytecode.segments[i]->instructions.size(); j++)
                    std::cout << j << '\t' << compiled_bytecode.segments[i]->instructions[j]->toString() << '\n';
                std::cout << '\n';
            }
        }
        interpreter.execute(compiled_bytecode);

        const auto stackTop = interpreter.vm.program_stack.top();
        if (stackTop.type != Bytecode::ObjectType::None)
            std::cout << stackTop.toString() << '\n';

        interpreter.vm.program_stack.clear();
    } catch (SyntaxError &error) {
        delete compiled_bytecode.segments[0];
        compiled_bytecode.segments[0] = new Bytecode::Segment({});
        interpreter.vm.call_stack.clear();
        std::cout << "SyntaxError (" << error.line
                  << ':' << error.column << "): "
                  << error.message << '\n';
    }
}

int main(int argc, char *argv[]) {
    struct options opts;

    int opt;
    while ((opt = getopt(argc, argv, "tbdO")) != -1) {
        switch (opt) {
            case 't':
                opts.displayTokens = true;
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
            } catch (ProgramExit &) {
                return EXIT_SUCCESS;
            }

            exec_program(userInput, opts);
        }
    }
}
