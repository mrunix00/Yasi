#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    class Interpreter {

    public:
        Interpreter() = default;
        void execute(const Program &program) {
            for (const auto instruction: program.segments[0]->instructions)
                instruction->execute(&vm);
        }
        VM vm;
    };
}// namespace Bytecode
