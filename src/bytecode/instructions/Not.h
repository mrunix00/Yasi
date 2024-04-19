#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Not final : public Instruction {
    public:
        Not() { type = InstructionType::Not; }
        [[nodiscard]] std::string toString() const override { return "Not"; }
    };
}// namespace Bytecode