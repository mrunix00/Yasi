#pragma once

#include "Register.h"
#include <iostream>

namespace Bytecode {
    class StdOutRegister final : public Register {
    public:
        explicit StdOutRegister() {
            type = RegisterType::StdOutRegister;
        }

        std::string toString() override {
            return "#stdout";
        }

        StackObject get(VM *vm) override {
            return StackObject{};
        }

        void store(VM *vm) override {
            const auto stackObject = vm->program_stack.pop();
            std::cout << stackObject.toString();
        }

        bool operator==(const Register &r) override {
            return type == RegisterType::StdOutRegister;
        }
    };
}// namespace Bytecode