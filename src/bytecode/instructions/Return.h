#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Return final : public Instruction {
    public:
        Return() {type = InstructionType::Return;}
        [[nodiscard]] std::string toString() const override {
            return "Return";
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode