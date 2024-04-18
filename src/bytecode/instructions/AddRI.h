#pragma once

#include "Instruction.h"

namespace Bytecode {
    class AddRI final : public Instruction {
    public:
        uint32_t rg;
        double number;
        AddRI(uint32_t rg, double number)
            : rg(rg), number(number) { type = InstructionType::AddRI; }
        [[nodiscard]] std::string toString() const override {
            return "AddRI $r" + std::to_string(rg) + ", " + StackObject(number).toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode