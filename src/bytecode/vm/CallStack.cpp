#include "CallStack.h"

namespace Bytecode {
    void CallStack::setLocal(const size_t reg, const StackObject sObject) const {
        local_registers[local_registers_used - stackTop->args + reg] = sObject;
    }

}// namespace Bytecode
