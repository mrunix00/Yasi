#pragma once

#include "Instruction.h"

namespace Bytecode {
    class LoadGlobal final : public Instruction {
    public:
        explicit LoadGlobal(const uint32_t reg) {
            this->reg = reg;
            type = InstructionType::LoadGlobal;
        }

        void execute(VM *vm) override {}

        [[nodiscard]] std::string toString() const override {
            return "LoadGlobal $g" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   instruction.reg == reg;
        }
    };
}