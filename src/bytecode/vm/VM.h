#ifndef YASI_VM_H
#define YASI_VM_H

#include "StackObject.h"
#include <vector>

namespace Bytecode {
    class VM {
        std::vector<StackObject *> program_stack;

    public:
        VM() = default;
        StackObject *StackTop();
        void Push(StackObject *);
    };
}// namespace Bytecode

#endif//YASI_VM_H
