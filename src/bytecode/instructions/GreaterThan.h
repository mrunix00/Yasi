#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
    };
}// namespace Bytecode
