#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    class Interpreter {
    public:
        Interpreter() = default;
        VM vm;
        void execute(const Program &program) {
            while(vm.current_line < program.segments[0]->instructions.size()) {
                program.segments[0]->instructions[vm.current_line++]->execute(&vm);
            }
        }
    };
}// namespace Bytecode
