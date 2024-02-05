#ifndef YASI_VM_H
#define YASI_VM_H

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
        StackObject* stackPop();
        void setGlobal(size_t i, StackObject *sObject);
        [[nodiscard]] StackObject* getGlobal(size_t i) const;
    };
}// namespace Bytecode

#endif//YASI_VM_H
