#include "VM.h"
namespace Bytecode {
    StackObject* VM::StackTop() {
        return program_stack.front();
    }
    void VM::Push(StackObject *object) {
        program_stack.push_back(object);
    }
}// namespace Bytecode