#pragma once

#include "Instruction.h"

namespace Bytecode {
    class DecrementR final : public Instruction {
    public:
        uint32_t rg;
        explicit DecrementR(uint32_t rg)
            : rg(rg){ type = InstructionType::DecrementR; }
        [[nodiscard]] std::string toString() const override {
            return "DecrementR $r" + std::to_string(rg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode