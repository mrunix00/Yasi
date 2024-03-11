#pragma once

#include "bytecode/compiler/Compiler.h"
#include "bytecode/vm/Interpreter.h"
#include "parser/Parser.h"
#include "utils/break_lines.h"
#include <gtest/gtest.h>
#include <string>

using namespace Bytecode;

inline StackObject run_program(const std::string &program) {
    const auto instructions = break_lines(program);
    auto compiler = Bytecode::Compiler(false);
    for (const auto &instruction: instructions) {
        auto tokens = Lexer::tokenize(instruction);
        const auto ast = Parser::parse(tokens);
        compiler.compile(*ast);
        delete ast;
    }

    auto interpreter = Bytecode::Interpreter();
    interpreter.execute(compiler.program);

    return interpreter.vm.program_stack.top();
}
