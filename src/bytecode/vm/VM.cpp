#include "VM.h"
namespace Bytecode {
    StackObject* VM::stackTop() const {
        return program_stack.back();
    }
    void VM::stackPush(StackObject *object) {
        program_stack.push_back(object);
    }
    StackObject* VM::stackPop() {
        auto object = program_stack.back();
        program_stack.pop_back();
        return object;
    }

    void VM::setGlobal(size_t i, StackObject *sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }
    StackObject* VM::getGlobal(const size_t i) const {
        return global_registers.at(i);
    }
}// namespace Bytecode