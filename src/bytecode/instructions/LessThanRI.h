#pragma once

#include "Instruction.h"
namespace Bytecode {
    class LessThanRI final : public Instruction {
    public:
        uint32_t rg;
        double number;
        LessThanRI(uint32_t rg, double number)
            : rg(rg), number(number) { type = InstructionType::LessThanRI; }
        [[nodiscard]] std::string toString() const override {
            return "LessThanRI $r" + std::to_string(rg) + ", " + StackObject(number).toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}