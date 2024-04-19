#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Return final : public Instruction {
    public:
        Return() { type = InstructionType::Return; }
        [[nodiscard]] std::string toString() const override { return "Return"; }
    };
}// namespace Bytecode