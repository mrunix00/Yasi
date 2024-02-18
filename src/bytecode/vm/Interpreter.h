#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    class Interpreter {
    public:
        Interpreter() = default;
        VM vm;
        void execute(const Program &program) {
            while (!(vm.getCurrentSegment() == 0 && vm.getCurrentLine() == program.segments[0]->instructions.size())) {
                auto currentInstruction = program.segments[vm.getCurrentSegment()]
                                                  ->instructions[vm.getCurrentLine()];
                if (vm.getCurrentLine() == program.segments[vm.getCurrentSegment()]->instructions.size()) {
                    vm.popStackFrame();
                } else {
                    currentInstruction->execute(&vm);
                }
                vm.nextLine();
            }
        }
    };
}// namespace Bytecode
