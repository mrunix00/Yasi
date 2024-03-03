#pragma once

#include "BooleanLiteral.h"
#include "NumberLiteral.h"
#include "Register.h"
#include "StringLiteral.h"
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
            const auto stackObject = vm->stackPop();
            switch (stackObject->type) {
                case StackObject::Boolean:
                    std::cout << (((BooleanLiteral *) stackObject)->asBoolean()
                                          ? std::string("#true")
                                          : std::string("#false"));
                    break;
                case StackObject::Number:
                    std::cout << ((NumberLiteral *) stackObject)->asNumber();
                    break;
                case StackObject::String:
                    std::cout << ((StringLiteral *) stackObject)->asString();
                    break;
                default:
                    std::cout << stackObject->toString();
            }
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