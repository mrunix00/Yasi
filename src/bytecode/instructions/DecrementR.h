#pragma once

#include "Instruction.h"

namespace Bytecode {
    class DecrementR final : public Instruction {
    public:
        explicit DecrementR(size_t reg) {
            params.r_param = {reg};
            type = InstructionType::DecrementR;
        }
        [[nodiscard]] std::string toString() const override {
            return "DecrementR $r" + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode