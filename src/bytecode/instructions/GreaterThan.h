#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
