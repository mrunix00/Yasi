#include "VM.h"
namespace Bytecode {
    StackObject* VM::stackTop() {
        return program_stack.front();
    }
    void VM::stackPush(StackObject *object) {
        program_stack.push_back(object);
    }
    StackObject* VM::stackPop() {
        auto object = program_stack.front();
        program_stack.pop_back();
        return object;
    }

    void VM::setGlobal(size_t i, StackObject *sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }
    StackObject* VM::getGlobal(size_t i) {
        return global_registers.at(i);
    }
}// namespace Bytecode