#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    class Interpreter {
    public:
        VM vm;
        Interpreter() = default;
        void execute(const Program &program);
    };
}// namespace Bytecode
