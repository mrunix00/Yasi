#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; }
        [[nodiscard]] std::string toString() const override { return "Add"; }
    };
}// namespace Bytecode
