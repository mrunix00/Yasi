#include "Interpreter.h"

namespace Bytecode {
    void Interpreter::execute(const Program &program) {
        while (true) {
            const auto currentLine = vm.call_stack.stackTop->current_line;
            const auto currentSegment = vm.call_stack.stackTop->segment;
            if (currentSegment == 0 &&
                currentLine == program.segments[0]->instructions.size()) {
                break;
            }
            const auto currentInstruction = program.segments[currentSegment]
                                                    ->instructions[currentLine];
            if (currentLine == program.segments[currentSegment]->instructions.size()) {
                vm.call_stack.popStackFrame();
            } else {
                currentInstruction->execute(&vm);
            }
            vm.call_stack.stackTop->current_line++;
        }
    }
}// namespace Bytecode