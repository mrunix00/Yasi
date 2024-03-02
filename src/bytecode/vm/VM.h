#pragma once

#include "bytecode/objects/StackObject.h"
#include <cstddef>
#include <vector>

namespace Bytecode {
    struct StackFrame {
        size_t current_line = 0;
        size_t segment = 0;
    };
    class VM {
        std::vector<StackObject *> program_stack;
        std::vector<StackObject *> global_registers;
        std::vector<std::vector<StackObject *>> local_registers;

    public:
        VM() {
            local_registers.emplace_back();
            call_stack.emplace_back();
        };
        [[nodiscard]] inline StackObject *stackTop() const {
            if (program_stack.empty()) return nullptr;
            return program_stack.back();
        }
        inline void stackPush(StackObject *object) {
            program_stack.push_back(object);
        }
        inline void jump(size_t line) {
            call_stack.back().current_line = line - 1;
        }
        inline StackObject *stackPop() {
            auto object = program_stack.back();
            program_stack.pop_back();
            return object;
        }
        void clearStack();
        void setGlobal(size_t i, StackObject *sObject);
        [[nodiscard]] StackObject *getGlobal(size_t i) const;
        void newStackFrame(size_t segment);
        void popStackFrame();
        void setLocal(size_t i, StackObject *sObject);
        inline StackObject *getLocal(size_t i) {
            return local_registers[local_registers.size() - 1][i];
        }
        std::vector<StackFrame> call_stack;
    };
}// namespace Bytecode
