#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CondJumpIfNot final : public Instruction {
    public:
        explicit CondJumpIfNot(const size_t line) {
            params.r_param = {line};
            type = InstructionType::CondJumpIfNot;
        }
        [[nodiscard]] std::string toString() const override {
            return "CondJumpIfNot " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
