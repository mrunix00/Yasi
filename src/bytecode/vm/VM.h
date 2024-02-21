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
        std::vector<StackFrame> call_stack;

    public:
        VM() {
                local_registers.emplace_back();
                call_stack.emplace_back();
        };
        [[nodiscard]] StackObject *stackTop() const;
        void stackPush(StackObject *object);
        void jump(size_t);
        StackObject* stackPop();
        void clearStack();
        void setGlobal(size_t i, StackObject *sObject);
        [[nodiscard]] StackObject* getGlobal(size_t i) const;
        void newStackFrame(size_t segment);
        void popStackFrame();
        void setLocal(size_t i, StackObject *sObject);
        StackObject* getLocal(size_t i);
        size_t getCurrentLine();
        void nextLine();
        size_t getCurrentSegment();
    };
}// namespace Bytecode
