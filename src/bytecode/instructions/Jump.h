#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Jump final : public Instruction {
    public:
        explicit Jump(const size_t line) {
            params.r_param.reg = line;
            type = InstructionType::Jump;
        }
        [[nodiscard]] std::string toString() const override {
            return "Jump " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
