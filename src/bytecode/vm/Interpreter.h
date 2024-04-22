#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    struct Interpreter {
        VM vm;
        void execute(const Program &program);
    };
}// namespace Bytecode
