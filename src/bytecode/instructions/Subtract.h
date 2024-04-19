#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
    };
}// namespace Bytecode
