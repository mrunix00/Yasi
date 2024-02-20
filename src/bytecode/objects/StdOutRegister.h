#pragma once

#include "Register.h"
#include <iostream>

namespace Bytecode {
    class StdOutRegister : public Register {
    public:
        std::string toString() override {
            return "#stdout";
        }

        StackObject *get(VM *vm) override {
            return nullptr;
        }

        void store(VM *vm) override {
            std::cout << vm->stackPop()->literal->int_literal << '\n';
        }

        bool operator==(const Register &r) override {
            return type == RegisterType::StdOutRegister;
        }

    public:
        explicit StdOutRegister() {
            type = RegisterType::StdOutRegister;
        }
    };
}// namespace Bytecode