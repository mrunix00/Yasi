#pragma once

#include "Register.h"

namespace Bytecode {
    class GlobalRegister : public Register {
        size_t reg;

    public:
        explicit GlobalRegister(size_t reg) : reg(reg) {
            type = RegisterType::GlobalRegister;
        }

        std::string toString() override {
            return "$g" + std::to_string(reg);
        }

        StackObject get(VM *vm) override {
            return vm->getGlobal(reg);
        }

        void store(VM *vm) override {
            auto object = vm->program_stack.pop();
            vm->setGlobal(reg, object);
        }

        bool operator==(const Register &r) override {
            return type == RegisterType::GlobalRegister &&
                   ((GlobalRegister *) &r)->reg == reg;
        }
    };
}// namespace Bytecode