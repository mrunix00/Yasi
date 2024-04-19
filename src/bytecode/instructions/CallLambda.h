#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CallLambda final : public Instruction {
    public:
        explicit CallLambda(const size_t args) {
            params.r_param = {args};
            type = InstructionType::CallLambda;
        }
        [[nodiscard]] std::string toString() const override {
            return "CallLambda " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode