#pragma once

#include "Register.h"

namespace Bytecode {
    class LocalRegister final : public Register {
        size_t reg;

    public:
        explicit LocalRegister(size_t reg) : reg(reg) {
            type = RegisterType::LocalRegister;
        }

        std::string toString() override {
            return "$r" + std::to_string(reg);
        }

        StackObject get(VM *vm) override {
            return vm->getLocal(reg);
        }

        void store(VM *vm) override {}

        bool operator==(const Register &r) override {
            return type == RegisterType::LocalRegister &&
                   ((LocalRegister *) &r)->reg == reg;
        }
    };
}// namespace Bytecode