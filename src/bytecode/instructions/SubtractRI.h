#pragma once

#include "Instruction.h"

namespace Bytecode {
    class SubtractRI final : public Instruction {
    public:
        uint32_t rg;
        double number;
        SubtractRI(uint32_t rg, double number)
            : rg(rg), number(number) { type = InstructionType::SubtractRI; }
        [[nodiscard]] std::string toString() const override {
            return "SubtractRI $r" + std::to_string(rg) + ", " + StackObject(number).toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode