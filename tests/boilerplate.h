#pragma once

#include "bytecode/vm/Interpreter.h"
#include "parser/Parser.h"
#include "utils/break_lines.h"
#include <gtest/gtest.h>
#include <string>

using namespace Bytecode;

inline StackObject run_program(const std::string &program) {
    const auto instructions = break_lines(program);
    auto compiled_program = Program();
    for (const auto &instruction: instructions) {
        auto tokens = Lexer::tokenize(instruction);
        const auto ast = Parser::parse(tokens);
        ast->compile(compiled_program.segments[0],
                     compiled_program,
                     compiled_program.segments[0]->instructions);
        delete ast;
    }

    auto interpreter = Bytecode::Interpreter();
    interpreter.execute(compiled_program);

    return interpreter.vm.program_stack.top();
}
