#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class LessThan final : public Instruction {
    public:
        LessThan() { type = InstructionType::LessThan; };
        [[nodiscard]] std::string toString() const override { return "LessThan"; }
    };
}// namespace Bytecode
