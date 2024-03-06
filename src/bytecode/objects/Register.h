#pragma once

#include "StackObject.h"
#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    class Register {
    protected:
        ~Register() = default;
        enum RegisterType {
            LocalRegister,
            GlobalRegister,
            None,
            StdOutRegister,
        };
        RegisterType type = None;

    public:
        virtual std::string toString() = 0;
        virtual void store(VM *vm) = 0;
        virtual StackObject get(VM *vm) = 0;
        virtual bool operator==(const Register &r) = 0;
    };
}// namespace Bytecode