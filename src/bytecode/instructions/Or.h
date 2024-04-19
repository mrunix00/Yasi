#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Or final : public Instruction {
    public:
        Or() {type = InstructionType::Or;}
        [[nodiscard]] std::string toString() const override {
            return "Or";
        }
    };
}// namespace Bytecode