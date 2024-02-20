#pragma once

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    class Register {
    protected:
        enum RegisterType {
            LocalRegister,
            GlobalRegister,
            None,
        };
        RegisterType type = None;

    public:
        virtual std::string toString() = 0;
        virtual void store(VM *vm) = 0;
        virtual StackObject* get(VM *vm) = 0;
        virtual bool operator==(const Register &r) = 0;
    };
}// namespace Bytecode