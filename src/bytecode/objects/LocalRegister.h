#pragma once

#include "Register.h"

namespace Bytecode {
    class LocalRegister : public Register {
        size_t reg;

    public:
        explicit LocalRegister(size_t reg) : reg(reg) {
            type = RegisterType::LocalRegister;
        }

        std::string toString() override {
            return "$r" + std::to_string(reg);
        }

        StackObject *get(VM *vm) override {
            return new StackObject(vm->getLocal(reg)->literal->copy());
        }

        void store(VM *vm) override {}

        bool operator==(const Register &r) override {
            return type == RegisterType::LocalRegister &&
                   ((LocalRegister *) &r)->reg == reg;
        }
    };
}// namespace Bytecode