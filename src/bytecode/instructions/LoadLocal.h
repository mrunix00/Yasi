#pragma once

#include "Instruction.h"

namespace Bytecode {
    class LoadLocal final : public Instruction {
    public:
        explicit LoadLocal(const uint32_t reg) {
            type = InstructionType::LoadLocal;
            this->reg = reg;
        }

        [[nodiscard]] std::string toString() const override {
            return "LoadLocal $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   instruction.reg == reg;
        }
    };
}// namespace Bytecode
