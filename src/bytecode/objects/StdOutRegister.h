#pragma once

#include "Register.h"
#include "StringLiteral.h"
#include "BooleanLiteral.h"
#include "NumberLiteral.h"
#include "DecimalNumberLiteral.h"
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
            const auto literal = vm->stackPop()->literal;
            switch (literal->type) {
                case Literal::Boolean:
                    std::cout << (((BooleanLiteral *) literal)->asBoolean()
                                          ? std::string("#true")
                                          : std::string("#false"));
                    break;
                case Literal::Number:
                    std::cout << ((NumberLiteral *) literal)->asNumber();
                    break;
                case Literal::DecimalNumber:
                    std::cout << ((DecimalNumberLiteral *) literal)->asDecimalNumber();
                    break;
                case Literal::String:
                    std::cout << ((StringLiteral *) literal)->asString();
                    break;
                default:
                    std::cout << literal->toString();
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