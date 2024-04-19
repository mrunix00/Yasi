#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
    };
}// namespace Bytecode
