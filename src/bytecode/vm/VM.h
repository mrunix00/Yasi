#pragma once

#include "CallStack.h"
#include "Stack.h"
#include <vector>

namespace Bytecode {
    class VM {
    public:
        Stack program_stack;
        CallStack call_stack;
        std::vector<StackObject> global_registers;

        VM() = default;

        void setGlobal(size_t i, StackObject sObject) {
            if (global_registers.size() < i)
                global_registers[i] = sObject;
            else if (global_registers.size() == i)
                global_registers.push_back(sObject);
        }

        StackObject getGlobal(size_t i) {
            return global_registers[i];
        }
    };
}// namespace Bytecode
