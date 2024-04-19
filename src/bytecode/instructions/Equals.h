#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        [[nodiscard]] std::string toString() const override { return "Equals"; }
    };
}// namespace Bytecode
