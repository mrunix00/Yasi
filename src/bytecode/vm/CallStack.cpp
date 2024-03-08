#include "CallStack.h"

namespace Bytecode {
    void CallStack::setLocal(size_t reg, const StackObject sObject) {
        local_registers[local_registers_used - 1][reg] = sObject;
    }

}// namespace Bytecode
