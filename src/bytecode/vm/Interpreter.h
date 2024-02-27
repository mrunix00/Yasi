#pragma once

#include "VM.h"
#include "bytecode/compiler/Program.h"

namespace Bytecode {
    class Interpreter {
    public:
        Interpreter() = default;
        VM vm;
        void execute(const Program &program) {
            while (true) {
                auto stackFrame = &vm.call_stack.back();
                auto currentLine = stackFrame->current_line;
                auto currentSegment = stackFrame->segment;
                if (currentSegment == 0 &&
                    currentLine == program.segments[0]->instructions.size()) {
                    break;
                }
                auto currentInstruction = program.segments[currentSegment]
                                                  ->instructions[currentLine];
                if (currentLine == program.segments[currentSegment]->instructions.size()) {
                    vm.popStackFrame();
                } else {
                    currentInstruction->execute(&vm);
                }
                vm.call_stack.back().current_line++;
            }
        }
    };
}// namespace Bytecode
