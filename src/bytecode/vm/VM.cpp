#include "VM.h"

namespace Bytecode {
    VM::VM() = default;

    void VM::setGlobal(const size_t i, const StackObject sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }

    StackObject VM::getGlobal(const size_t i) const {
        return global_registers.at(i);
    }
}// namespace Bytecode