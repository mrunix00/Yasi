#include "Interpreter.h"
#include "exceptions/SyntaxError.h"

#include <algorithm>
#include <iostream>

void Bytecode::Interpreter::execute(const Program &program) {
    const auto &stackTop = vm.call_stack.stackTop;
    for (;; stackTop->current_line++) {
        const auto currentSegment =
                program.segments[stackTop->segment];
        if (stackTop->segment == 0 &&
            stackTop->current_line == currentSegment->instructions.size())
            return;
        currentSegment->instructions[stackTop->current_line]->execute(vm);
    }
}
