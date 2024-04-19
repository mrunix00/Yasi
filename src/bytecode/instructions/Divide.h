#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        [[nodiscard]] std::string toString() const override { return "Divide"; }
    };
}// namespace Bytecode
