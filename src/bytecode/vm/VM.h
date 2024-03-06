#pragma once

#include "Stack.h"
#include "bytecode/objects/StackObject.h"
#include <cstddef>
#include <vector>

namespace Bytecode {
    struct StackFrame {
        size_t current_line = 0;
        size_t segment = 0;
    };
    class VM {
        std::vector<StackObject> global_registers;
        std::vector<std::vector<StackObject>> local_registers;

    public:
        Stack program_stack;
        std::vector<StackFrame> call_stack;

        VM() {
            local_registers.emplace_back();
            call_stack.emplace_back();
        };
        inline void jump(size_t line) {
            call_stack.back().current_line = line - 1;
        }
        void setGlobal(size_t i, StackObject sObject);
        [[nodiscard]] StackObject getGlobal(size_t i) const;
        void newStackFrame(size_t segment);
        void popStackFrame();
        void setLocal(size_t i, StackObject sObject);
        inline StackObject getLocal(size_t i) {
            return local_registers[local_registers.size() - 1][i];
        }
    };
}// namespace Bytecode
