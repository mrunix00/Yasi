#pragma once

#include "Instruction.h"

namespace Bytecode {
    class And final : public Instruction {
    public:
        And() {type = InstructionType::And;}
        [[nodiscard]] std::string toString() const override {
            return "And";
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode