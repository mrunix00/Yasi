#ifndef YASI_VM_H
#define YASI_VM_H

#include "StackObject.h"
#include <vector>

namespace Bytecode {
    class VM {
        std::vector<StackObject *> program_stack;
        std::vector<StackObject *> global_registers;

    public:
        VM() = default;
        StackObject *stackTop();
        void stackPush(StackObject *object);
        StackObject* stackPop();
        void setGlobal(size_t i, StackObject *sObject);
        StackObject* getGlobal(size_t i);
    };
}// namespace Bytecode

#endif//YASI_VM_H
