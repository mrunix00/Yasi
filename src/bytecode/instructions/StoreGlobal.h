#pragma once

#include "Instruction.h"
#include <string>

namespace Bytecode {
    class StoreGlobal final : public Instruction {
    public:
        explicit StoreGlobal(const size_t reg) {
            this->reg = reg;
            type = InstructionType::StoreGlobal;
        }

        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Store $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   instruction.reg == reg;
        }
    };
}// namespace Bytecode
