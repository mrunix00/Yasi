#include "Interpreter.h"

namespace Bytecode {
    void Interpreter::execute(const Program &program) {
        while (true) {
            const auto stackFrame = &vm.call_stack.back();
            const auto currentLine = stackFrame->current_line;
            const auto currentSegment = stackFrame->segment;
            if (currentSegment == 0 &&
                currentLine == program.segments[0]->instructions.size()) {
                break;
            }
            const auto currentInstruction = program.segments[currentSegment]
                                                    ->instructions[currentLine];
            if (currentLine == program.segments[currentSegment]->instructions.size()) {
                vm.popStackFrame();
            } else {
                currentInstruction->execute(&vm);
            }
            vm.call_stack.back().current_line++;
        }
    }
}// namespace Bytecode