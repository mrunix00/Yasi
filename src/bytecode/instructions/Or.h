#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Or final : public Instruction {
    public:
        Or() {type = InstructionType::Or;}
        [[nodiscard]] std::string toString() const override {
            return "Or";
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode