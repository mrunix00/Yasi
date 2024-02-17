#pragma once

#include "StackObject.h"
#include <vector>
#include <cstddef>

namespace Bytecode {
    class VM {
        std::vector<StackObject *> program_stack;
        std::vector<StackObject *> global_registers;

    public:
        VM() = default;
        [[nodiscard]] StackObject *stackTop() const;
        void stackPush(StackObject *object);
        void jump(size_t);
        StackObject* stackPop();
        void setGlobal(size_t i, StackObject *sObject);
        [[nodiscard]] StackObject* getGlobal(size_t i) const;
        size_t current_line = 0;
    };
}// namespace Bytecode
