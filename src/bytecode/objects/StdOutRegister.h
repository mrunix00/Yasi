#pragma once

#include "Register.h"
#include <iostream>

namespace Bytecode {
    class StdOutRegister : public Register {
    public:
        std::string toString() override {
            return "#stdout";
        }

        StackObject get(VM *vm) override {
            return StackObject{};
        }

        void store(VM *vm) override {
            const auto stackObject = vm->program_stack.pop();
            switch (stackObject.type) {
                case Boolean:
                    std::cout << (stackObject.asBoolean()
                                          ? std::string("#true")
                                          : std::string("#false"));
                    break;
                case Number:
                    std::cout << stackObject.asNumber();
                    break;
                case String: {
                    const std::string string = stackObject.asString();
                    if (string[0] == '"' && string.back() == '"')
                        std::cout << string.substr(1, string.size() - 2);
                    else
                        std::cout << string;
                } break;
                default:
                    break;
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