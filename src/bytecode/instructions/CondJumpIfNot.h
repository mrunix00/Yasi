#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CondJumpIfNot final : public Instruction {
    public:
        explicit CondJumpIfNot(const uint32_t line) {
            param = line;
            type = InstructionType::CondJumpIfNot;
        }
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "CondJumpIfNot " + std::to_string(param);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   param == instruction.param;
        }
    };
}// namespace Bytecode
