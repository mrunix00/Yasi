#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
