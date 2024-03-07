#pragma once

#include "CallStack.h"
#include "Stack.h"
#include "bytecode/objects/StackObject.h"
#include <cstddef>
#include <vector>

namespace Bytecode {
    class VM {
        std::vector<StackObject> global_registers;

    public:
        Stack program_stack;
        CallStack call_stack;

        VM();
        void setGlobal(size_t i, StackObject sObject);
        [[nodiscard]] StackObject getGlobal(size_t i) const;
    };
}// namespace Bytecode
