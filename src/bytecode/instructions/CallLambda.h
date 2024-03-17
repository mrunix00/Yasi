#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CallLambda final : public Instruction {
    public:
        explicit CallLambda(const size_t args) {
            this->param = args;
            type = InstructionType::CallLambda;
        }
        [[nodiscard]] std::string toString() const override {
            return "CallLambda " + std::to_string(param);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   instruction.reg == reg &&
                   instruction.param == param;
        }
    };
}