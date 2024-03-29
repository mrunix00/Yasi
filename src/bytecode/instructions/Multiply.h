#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
