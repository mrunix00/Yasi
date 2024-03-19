#pragma once

#include "Stack.h"
#include "bytecode/objects/StackObject.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace Bytecode {
    struct StackFrame {
        uint32_t segment;
        uint32_t current_line;
        uint32_t args;
    };

    class CallStack {
        StackFrame *stack;
        size_t stackframe_capacity;
        size_t stackframe_used;

        StackObject *local_registers;
        size_t local_registers_capacity;
        size_t local_registers_used;

    public:
        StackFrame *stackTop;

        CallStack() {
            stackframe_capacity = 512;
            local_registers_capacity = 512;
            local_registers_used = 0;

            local_registers = (StackObject *) malloc(local_registers_capacity *
                                                     sizeof(StackObject));
            stack = (StackFrame *) malloc(stackframe_capacity * sizeof(StackFrame));

            if (local_registers == nullptr || stack == nullptr) {
                std::cerr << "Failed to allocate memory for the call stack!" << std::endl;
                exit(1);
            }

            stackTop = stack;
            stackframe_used = 0;
            newStackFrame(0);
            stackTop->current_line++;
        }

        ~CallStack() {
            free(stack);
        }

        void newStackFrame(const uint32_t segment) {
            newStackFrame(segment, 0, nullptr);
        }

        void newStackFrame(const uint32_t segment, const uint32_t args, Stack *program_stack) {
            if (stackframe_used + 1 > stackframe_capacity) {
                stackframe_capacity *= 2;
                auto temp = realloc(stack, stackframe_capacity * sizeof(StackFrame));
                if (temp == nullptr) {
                    std::cerr << "Failed to allocate memory for the call stack!" << std::endl;
                    exit(1);
                }
                stack = (StackFrame *) temp;
            }
            stackTop = stack + stackframe_used;
            stack[stackframe_used++] = StackFrame{
                    segment,
                    static_cast<uint32_t>(-1),
                    args,
            };

            if (local_registers_used + args > local_registers_capacity) {
                local_registers_capacity *= 2;
                auto temp = realloc(local_registers, local_registers_capacity *
                                                             sizeof(StackObject));
                if (temp == nullptr) {
                    std::cerr << "Failed to allocate memory for the call stack!" << std::endl;
                    exit(1);
                }
                local_registers = (StackObject *) temp;
            }
            local_registers_used += args;

            if (program_stack != nullptr)
                for (auto i = args - 1; i + 1 != 0; i--)
                    setLocal(i, program_stack->pop());
        }

        void popStackFrame() {
            if (local_registers_used != 0 &&
                ((int) (local_registers_used - stackTop->args)) >= 0)
                local_registers_used -= stackTop->args;
            if (stackframe_used != 0)
                stackframe_used--;
            stackTop = stack + stackframe_used - 1;
        }

        [[nodiscard]] StackObject getLocal(const size_t reg) const {
            return local_registers[local_registers_used - stackTop->args + reg];
        }

        void setLocal(const size_t reg, const StackObject sObject) const {
            local_registers[local_registers_used - stackTop->args + reg] = sObject;
        }
    };
}// namespace Bytecode