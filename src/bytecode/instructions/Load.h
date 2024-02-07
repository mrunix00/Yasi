#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Load final : public Instruction {
        size_t reg;

    public:
        explicit Load(const size_t reg) : reg(reg) { type = InstructionType::Load; };
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Load $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                dynamic_cast<const Load *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
