#include "CallStack.h"

namespace Bytecode {
    void CallStack::setLocal(uint32_t reg, const StackObject sObject) {
        const auto registers = &local_registers.back();
        while (registers->size() < reg + 1)
            registers->emplace_back();
        registers->at(reg) = sObject;
    }
}// namespace Bytecode
