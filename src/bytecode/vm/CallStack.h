#pragma once

#include "bytecode/objects/StackObject.h"
#include <cstdint>
#include <cstdlib>
#include <vector>

namespace Bytecode {
    struct StackFrame {
        uint32_t segment;
        uint32_t current_line;
    };

    class CallStack {
        StackFrame *stack;
        size_t capacity;
        size_t used;
        std::vector<std::vector<StackObject>> local_registers;

    public:
        StackFrame *stackTop;

        CallStack() {
            capacity = 512;
            stack = (StackFrame *) malloc(capacity * sizeof(StackFrame));
            stackTop = stack;
            used = 0;
            newStackFrame(0);
            stackTop->current_line++;
            local_registers.emplace_back();
        }

        ~CallStack() {
            free(stack);
        }

        void newStackFrame(uint32_t segment) {
            local_registers.emplace_back();
            if (used + 1 > capacity) {
                capacity *= 2;
                stack = (StackFrame *) realloc(stack, capacity);
            }
            stackTop = stack + used;
            stack[used++] = StackFrame{segment, static_cast<uint32_t>(-1)};
        }

        void popStackFrame() {
            if (used != 0)
                used--;
            if (!local_registers.empty())
                local_registers.pop_back();
            stackTop = stack + used - 1;
        }

        void jump(uint32_t line) {
            stack[used - 1].current_line = line - 1;
        }

        StackObject getLocal(uint32_t reg) {
            return local_registers[local_registers.size() - 1][reg];
        }

        void setLocal(uint32_t reg, StackObject sObject);
    };
}// namespace Bytecode